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
        public static string ComputeSHA3(string filename) {
            var fileBytes = File.ReadAllBytes(filename);
            var hashRaw = DigestUtilities.CalculateDigest("SHA3-384", fileBytes);
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
            var encryptedStream = new BcpgOutputStream(armoredStream);
            sigGen.GenerateOnePassVersion(false).Encode(encryptedStream);

            var inStream = new MemoryStream(Encoding.ASCII.GetBytes(hash));

            var literalGenerator = new PgpLiteralDataGenerator();
            var literalOut = literalGenerator.Open(encryptedStream, PgpLiteralData.Binary, "hash", hash.Length, DateTime.Now);

            int ch;
            while((ch = inStream.ReadByte()) >= 0) {
                literalOut.WriteByte((byte)ch);
                sigGen.Update((byte)ch);
            }
            
            inStream.Dispose();
            literalGenerator.Close();

            sigGen.Generate().Encode(encryptedStream);

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

        public static byte[] CipherFile(bool encrypt, string filename, string key) {
            var iv = new byte[16];
            var inBytes = File.ReadAllBytes(filename);
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