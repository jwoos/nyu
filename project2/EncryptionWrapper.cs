using System;
using System.IO;
using System.Linq;
using System.Text;
using Org.BouncyCastle.Bcpg;
using Org.BouncyCastle.Bcpg.OpenPgp;
using Org.BouncyCastle.Crypto;
using Org.BouncyCastle.Crypto.Engines;
using Org.BouncyCastle.Crypto.Modes;
using Org.BouncyCastle.Crypto.Paddings;
using Org.BouncyCastle.Crypto.Parameters;
using Org.BouncyCastle.Security;
using Org.BouncyCastle.Utilities.Encoders;

namespace Park {
    public static class Encryption {
        public static string ComputeSHA3(byte[] data) {
            var hashRaw = DigestUtilities.CalculateDigest("SHA3-384", data);
            var hash = Hex.ToHexString(hashRaw);
            return hash;
        }
        public static string Sign(string hash, string keyFile, string keyPass) {
            var outStream = new MemoryStream();
            var armoredStream = new ArmoredOutputStream(outStream);

            var secretKey = ReadSigningKey(keyFile);
            var privateKey = secretKey.ExtractPrivateKey(keyPass.ToCharArray());
            var sigGen = new PgpSignatureGenerator(secretKey.PublicKey.Algorithm, HashAlgorithmTag.Sha384);
            sigGen.InitSign(PgpSignature.BinaryDocument, privateKey);
            foreach(string userId in secretKey.PublicKey.GetUserIds()) {
                var subpacketGenerator = new PgpSignatureSubpacketGenerator();
                subpacketGenerator.SetSignerUserId(false, userId);
                sigGen.SetHashedSubpackets(subpacketGenerator.Generate());
                break;
            }
            var signedStream = new BcpgOutputStream(armoredStream);
            sigGen.GenerateOnePassVersion(false).Encode(signedStream );

            var inStream = new MemoryStream(Encoding.ASCII.GetBytes(hash));

            var literalGenerator = new PgpLiteralDataGenerator();
            var literalOut = literalGenerator.Open(signedStream , PgpLiteralData.Binary, "hash", hash.Length, DateTime.Now);

            int ch;
            while((ch = inStream.ReadByte()) >= 0) {
                literalOut.WriteByte((byte)ch);
                sigGen.Update((byte)ch);
            }
            
            inStream.Dispose();
            literalGenerator.Close();

            sigGen.Generate().Encode(signedStream);

            armoredStream.Dispose();

            return Encoding.ASCII.GetString(outStream.ToArray());
        }

        public static bool Verify(string hash, string signature, string publicKey) {
            try {
                var signatureStream = new MemoryStream(Encoding.ASCII.GetBytes(signature));
                var decoderStream = PgpUtilities.GetDecoderStream(signatureStream);

                PgpObjectFactory            pgpObjectFactory = new PgpObjectFactory(decoderStream);
            
                PgpOnePassSignatureList     signatureList = (PgpOnePassSignatureList) pgpObjectFactory.NextPgpObject();
                PgpOnePassSignature         onePassSignature = signatureList[0];

                PgpLiteralData              literalData = (PgpLiteralData) pgpObjectFactory.NextPgpObject();
                Stream                      literalStream = literalData.GetInputStream();
                FileStream                  keyFile = File.OpenRead(publicKey);
                PgpPublicKeyRingBundle      pgpRing = new PgpPublicKeyRingBundle(PgpUtilities.GetDecoderStream(keyFile));
                PgpPublicKey                key = pgpRing.GetPublicKey(onePassSignature.KeyId);
                Stream                      outStream = new MemoryStream();

                onePassSignature.InitVerify(key);

                int ch;
                while ((ch = literalStream.ReadByte()) >= 0)
                {
                    onePassSignature.Update((byte)ch);
                    outStream.WriteByte((byte) ch);
                }
                var hashStream = new MemoryStream(Encoding.ASCII.GetBytes(hash));
                outStream.Seek(0, SeekOrigin.Begin);
                if(hashStream.Length != outStream.Length) {
                    return false;
                }
                int left, right;
                while((left = hashStream.ReadByte()) >= 0 && (right = outStream.ReadByte()) >= 0) {
                    if(left != right) {
                        return false;
                    }
                }
                outStream.Dispose();

                PgpSignatureList    signatureList2 = (PgpSignatureList)pgpObjectFactory.NextPgpObject();
                PgpSignature        firstSig = signatureList2[0];
                if (onePassSignature.Verify(firstSig))
                {
                    return true;
                }
                else
                {
                    return false;
                }
            } catch {
                return false;
            }
        }

        public static string GenerateKey() {
            var keyGenerator = Org.BouncyCastle.Security.GeneratorUtilities.GetKeyGenerator("AES");
            var randomSource = new SecureRandom();
            keyGenerator.Init(new Org.BouncyCastle.Crypto.KeyGenerationParameters(randomSource, 256));
            return Hex.ToHexString(keyGenerator.GenerateKey());
        }

        public static byte[] CipherFile(bool encrypt, byte[] inBytes, string key) {
            var iv = new byte[16];
            if(encrypt) {
                var secureRandom = new SecureRandom();
                secureRandom.NextBytes(iv, 0, 16);
            } else {
                Array.Copy(inBytes, iv, 16);
            }
            var cipher = CipherUtilities.GetCipher("AES/CTR/NoPadding");
            var keyParameter = new KeyParameter(Hex.Decode(key));
            var keyAndIV = new ParametersWithIV(keyParameter, iv, 0, 16);
            cipher.Init(encrypt, keyAndIV);
            var result = new byte[cipher.GetOutputSize(inBytes.Length)];
            var offset = encrypt ? 0 : 16;
            int size1 = cipher.ProcessBytes(inBytes, offset, inBytes.Length - offset, result, 0);
            int size2 = cipher.DoFinal(result, size1);
            if(encrypt) {
                var final = new byte[16 + size1 + size2];
                Array.Copy(iv, final, 16);
                Array.Copy(result, 0, final, 16, size1 + size2);
                return final;
            } else {
                var final = new byte[size1 + size2];
                Array.Copy(result, 0, final, 0, size1 + size2);
                return final;
            }
        }

        public static string EncryptKeyFor(string aesKeyToEncrypt, string publicKeyText) {
            var publicKey = ReadPublicKey(publicKeyText);
            var literalByteStream = new MemoryStream();

            var literalDataGenerator = new PgpLiteralDataGenerator();

            var pOut = literalDataGenerator.Open(
                literalByteStream,      // A stream for all the literal data
                PgpLiteralData.Binary,
                "key",                  // "filename" to store
                aesKeyToEncrypt.Length, // length of clear data
                DateTime.UtcNow         // current time
            );

            pOut.Write(Encoding.ASCII.GetBytes(aesKeyToEncrypt), 0, aesKeyToEncrypt.Length);

            literalDataGenerator.Close();

            var encryptedDataGenerator = new PgpEncryptedDataGenerator(SymmetricKeyAlgorithmTag.Aes256, new SecureRandom());

            encryptedDataGenerator.AddMethod(publicKey);

            byte[] literalBytes = literalByteStream.ToArray();

            MemoryStream encryptedStream = new MemoryStream();
            var armoredStream = new ArmoredOutputStream(encryptedStream);

            Stream cOut = encryptedDataGenerator.Open(armoredStream, literalBytes.Length);
            cOut.Write(literalBytes, 0, literalBytes.Length);  // obtain the actual bytes from the compressed stream
            cOut.Dispose();
            armoredStream.Dispose();

            return Encoding.ASCII.GetString(encryptedStream.ToArray());
        }

        public static string DecryptKey(string encryptedAESKey, string privateKeyFilename, string passPhrase) {
            var inputStream = new MemoryStream(Encoding.ASCII.GetBytes(encryptedAESKey));
            var armoredStream = new ArmoredInputStream(inputStream);
            //var decoderStream = PgpUtilities.GetDecoderStream(inputStream);

            try
            {
                PgpObjectFactory pgpF = new PgpObjectFactory(armoredStream);
                PgpEncryptedDataList enc;

                PgpObject o = pgpF.NextPgpObject();
                //
                // the first object might be a PGP marker packet.
                //
                if (o is PgpEncryptedDataList)
                {
                    enc = (PgpEncryptedDataList)o;
                }
                else
                {
                    enc = (PgpEncryptedDataList)pgpF.NextPgpObject();
                }

                //
                // find the secret key
                //
                PgpPrivateKey sKey = ReadPrivateKey(privateKeyFilename, passPhrase);

                if (sKey == null)
                {
                    throw new ArgumentException("secret key for message not found.");
                }
                
                PgpPublicKeyEncryptedData pbe = null;
                foreach(var pked in enc.GetEncryptedDataObjects().Cast<PgpPublicKeyEncryptedData>()) {
                    if(pked.KeyId == sKey.KeyId) {
                        pbe = pked;
                        break;
                    }
                }
                if(pbe == null) {
                    Console.WriteLine("Invalid Key");
                    return "";
                }
                var cleartextStream = pbe.GetDataStream(sKey);

                var plainObjectFactory = new PgpObjectFactory(cleartextStream);

                var message = plainObjectFactory.NextPgpObject();
                var result = "";
                if (message is PgpLiteralData)
                {
                    PgpLiteralData ld = (PgpLiteralData)message;

                    var output = new MemoryStream();
                    var decrypted = ld.GetInputStream();
                    decrypted.CopyTo(output);
                    result = Encoding.ASCII.GetString(output.ToArray());
                }
                else
                {
                    throw new PgpException("message is not a simple encrypted file - type unknown.");
                }

                if (pbe.IsIntegrityProtected())
                {
                    if (!pbe.Verify())
                    {
                        Console.Error.WriteLine("message failed integrity check");
                    }
                    else
                    {
                        Console.Error.WriteLine("message integrity check passed");
                    }
                }
                return result;
            }
            catch (PgpException e)
            {
                Console.Error.WriteLine(e);

                Exception underlyingException = e.InnerException;
                if (underlyingException != null)
                {
                    Console.Error.WriteLine(underlyingException.Message);
                    Console.Error.WriteLine(underlyingException.StackTrace);
                }
            }
            return "";
        }
        private static PgpPublicKey ReadPublicKey(string publicKey) {
            var keyStream = new MemoryStream(Encoding.ASCII.GetBytes(publicKey));
            var decoderStream = PgpUtilities.GetDecoderStream(keyStream);
            var keyBundle = new PgpPublicKeyRingBundle(decoderStream);
            foreach(var keyRing in keyBundle.GetKeyRings().Cast<PgpPublicKeyRing>()) {
                foreach(var key in keyRing.GetPublicKeys().Cast<PgpPublicKey>()) {
                    if(key.IsEncryptionKey) {
                        return key;
                    }
                }
            }
            return null;
        }
        private static PgpPrivateKey ReadPrivateKey(string keyFile, string passPhrase) {
            var keyStream = File.OpenRead(keyFile);
            var decoderStream = PgpUtilities.GetDecoderStream(keyStream);
            var keyBundle = new PgpSecretKeyRingBundle(decoderStream);
            foreach(var keyRing in keyBundle.GetKeyRings().Cast<PgpSecretKeyRing>()) {
                foreach(var key in keyRing.GetSecretKeys().Cast<PgpSecretKey>()) {
                    if(!key.IsPrivateKeyEmpty) {
                        return key.ExtractPrivateKey(passPhrase.ToCharArray());
                    }
                }
            }
            return null;
        }
        private static PgpSecretKey ReadSigningKey(string keyFile) {
            var keyStream = File.OpenRead(keyFile);
            var decoderStream = PgpUtilities.GetDecoderStream(keyStream);
            var keyBundle = new PgpSecretKeyRingBundle(decoderStream);
            PgpSecretKey signingKey = null;
            foreach(var keyRing in keyBundle.GetKeyRings().Cast<PgpSecretKeyRing>()) {
                foreach(var key in keyRing.GetSecretKeys().Cast<PgpSecretKey>()) {
                    if(key.IsSigningKey) {
                        signingKey = key;
                    }
                }
            }
            keyStream.Dispose();
            return signingKey;
        } 
    }

}