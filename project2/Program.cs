using System;
using System.Linq;
using Keybase;
using clipr;
using System.IO;
using System.Collections.Generic;
using Newtonsoft.Json;


using Org.BouncyCastle;
using Org.BouncyCastle.Bcpg.OpenPgp;
using Org.BouncyCastle.Security;
using Org.BouncyCastle.Utilities.IO;
using Org.BouncyCastle.Utilities.Encoders;
using Org.BouncyCastle.Bcpg;
using System.Text;

namespace Park
{
    [ApplicationInfo(Description = "Command line options")]
    public class Options {
        [clipr.NamedArgument('i', "in", Description = "The file to encrypt")]
        public string inFile { get; set; }
        [clipr.NamedArgument('e', "encrypted", Description = "The file, in encrypted form")]
        public string encryptedFile { get; set; }
        [clipr.NamedArgument('l', "link", Description = "Link to the publicly hosted / encrypted file")]
        public string link { get; set; }
        [clipr.NamedArgument('m', "me", Description = "My own keybase username")]
        public string me { get; set; }
        [clipr.NamedArgument('k', "key", Description = "The private key used for signing")]
        public string keyFile { get; set; }
        [PromptIfValueMissing(MaskInput = true)]
        [clipr.NamedArgument('p', "passphrase", Description = "Passphrase for the chosen key")]
        public string keyPassword { get; set; }
        [clipr.NamedArgument('r', "recipient", Description = "Any recipients who should be able to access the file", Action = clipr.ParseAction.Append)]
        public List<string> recipients { get; set; }
    }

    class Program
    {
        static void Main(string[] args)
        {
            
            var options = CliParser.Parse<Options>(args);
            
            var serialized = Newtonsoft.Json.JsonConvert.SerializeObject(options, Formatting.Indented);
            Console.WriteLine(serialized);

            var realFile = File.ReadAllBytes("sample/fileReal.txt");
            var fakeFile = File.ReadAllBytes("sample/fileFake.txt");
            
            var realHash = Encryption.ComputeSHA3(realFile);
            var fakeHash = Encryption.ComputeSHA3(fakeFile);

            var realSignature = Encryption.Sign(realHash, "sample/privateReal", "sample_password");
            var modifiedHashSig = Encryption.Sign(fakeHash, "sample/privateReal", "sample_password");
            var otherKeySig = Encryption.Sign(realHash, "sample/privateFake", "attacker_password");

            Console.WriteLine($"Hash of real file: {realHash}");            
            Console.WriteLine($"Signature of real file:\n{realSignature}");

            Console.WriteLine($"Hash of fake file: {fakeHash}");
            Console.WriteLine($"Signature of fake file with real key:\n{modifiedHashSig}");

            Console.WriteLine($"Signature of real file with fake key:\n{otherKeySig}");

            Console.WriteLine("Verifications: ");
            Console.WriteLine($"Real hash, Real signature, Real key: {Encryption.Verify(realHash, realSignature, "sample/publicReal")}  => Should Be True");
            Console.WriteLine($"Real hash, Real signature, Fake key: {Encryption.Verify(realHash, realSignature, "sample/publicFake")} => Should Be False");
            Console.WriteLine($"Real hash, Modified Sig,   Real key: {Encryption.Verify(realHash, modifiedHashSig, "sample/publicReal")} => Should Be False");
            Console.WriteLine($"Real hash, Modified Sig,   Fake key: {Encryption.Verify(realHash, modifiedHashSig, "sample/publicFake")} => Should Be False");
            Console.WriteLine($"Fake hash, Real signature, Real key: {Encryption.Verify(fakeHash, realSignature, "sample/publicReal")} => Should Be False");
            Console.WriteLine($"Fake hash, Real signature, Fake key: {Encryption.Verify(fakeHash, realSignature, "sample/publicFake")} => Should Be False");
            Console.WriteLine($"Fake hash, Modified Sig,   Real key: {Encryption.Verify(fakeHash, modifiedHashSig, "sample/publicReal")}  => Should Be True");
            Console.WriteLine($"Fake hash, Modified Sig,   Fake key: {Encryption.Verify(fakeHash, modifiedHashSig, "sample/publicFake")} => Should Be False");
            Console.WriteLine($"Real hash, Other Key Sig,  Real key: {Encryption.Verify(realHash, otherKeySig, "sample/publicReal")} => Should Be False");
            Console.WriteLine($"Real hash, Other Key Sig,  Fake key: {Encryption.Verify(realHash, otherKeySig, "sample/publicFake")}  => Should Be True");
            Console.WriteLine($"Fake hash, Other Key Sig,  Real key: {Encryption.Verify(fakeHash, otherKeySig, "sample/publicReal")} => Should Be False");
            Console.WriteLine($"Fake hash, Other Key Sig,  Fake key: {Encryption.Verify(fakeHash, otherKeySig, "sample/publicFake")} => Should Be False");
            Console.WriteLine();

            var key = "a648b47619bea69a8ae7c8075f8c82018213c67a675431f12b02a608f52753a9"; //Encryption.GenerateKey();
            Console.WriteLine($"Generated key: {key}");
            var encryptedFile = Encryption.CipherFile(true, realFile, key);
            var decryptedFile = Encryption.CipherFile(false, encryptedFile, key);

            var hashOfEncrypted = Encryption.ComputeSHA3(encryptedFile);
            var signatureForEncrypted = Encryption.Sign(hashOfEncrypted, "sample/privateReal", "sample_password");

            Console.WriteLine($"file == decrypt(encrypt(file))? {realFile.SequenceEqual(decryptedFile)}");

            var encKey = Encryption.EncryptKeyFor(key, File.ReadAllText("sample/publicReal"));
            var decKey = Encryption.DecryptKey(encKey, "sample/privateReal", "sample_password");

            var encKeyOther = Encryption.EncryptKeyFor(key, File.ReadAllText("sample/publicFake"));

            Console.WriteLine($"key == decrypt(encrypt(key))?  {key == decKey}");
            
            Console.ReadLine();

            var keybaseMe = Keybase.API.Lookup(options.me);

            var keybaseUsers = options.recipients.Select(u => Keybase.API.Lookup(u))
                .Where(u => u.them.Count > 0 && u.them[0].public_keys?.primary?.bundle != null);
            var recipients = keybaseUsers.Select(u => {
                var encrypted = Encryption.EncryptKeyFor(key, u.them[0].public_keys.primary.bundle);
                Console.WriteLine($"{u.them[0].basics.username}\n{encrypted}");
                return new Output.Payload.Party {
                    keybaseUsername = u.them[0].basics.username,
                    keyFingerprint = u.them[0].public_keys.primary.key_fingerprint,
                    encryptionAlgorithm = "PGP RsaGeneral",
                    encryptedKey = encrypted,
                };
            });

            var payload = new Output.Payload {
                sender = new Output.Payload.Party {
                    keybaseUsername = options.me,
                    keyFingerprint = keybaseMe.them[0].public_keys.primary.key_fingerprint,
                    encryptionAlgorithm = "PGP RsaGeneral",
                    encryptedKey = Encryption.EncryptKeyFor(key, keybaseMe.them[0].public_keys.primary.bundle),
                },
                recipients = recipients.ToList(),
                preSignature = new Output.Signature {
                    hashAlgorithm = "SHA3-384",
                    signatureAlgorithm = "PGP RsaGeneral Sha384",
                    signature = realSignature,
                },
                postSignature = new Output.Signature {
                    hashAlgorithm = "SHA3-384",
                    signatureAlgorithm = "PGP RsaGeneral Sha384",
                    signature = signatureForEncrypted
                }
            };
            var payloadJSON = Newtonsoft.Json.JsonConvert.SerializeObject(payload, Formatting.None);
            var payloadHash = Encryption.ComputeSHA3(Encoding.ASCII.GetBytes(payloadJSON));
            var payloadSignature = Encryption.Sign(payloadHash, "sample/privateReal", "sample_password");
            var output = new Output {
                payload = payload,
                
                payloadSignature = new Output.Signature {
                    hashAlgorithm = "SHA3-384",
                    signatureAlgorithm = "PGP RsaGeneral Sha384",
                    signature = payloadSignature
                },
                fileMeta = new Output.File {
                    encryptionAlgorithm = "AES/CTR/NoPadding",
                    link = "Unhosted",
                }
            };

            var outputJSON = Newtonsoft.Json.JsonConvert.SerializeObject(output, Formatting.Indented);
            Console.WriteLine();
            Console.WriteLine(outputJSON);
            Console.ReadLine();

            var deserializedOutput = Newtonsoft.Json.JsonConvert.DeserializeObject<Output>(outputJSON);
            var serializedpayload = Newtonsoft.Json.JsonConvert.SerializeObject(deserializedOutput.payload, Formatting.None);
            var payloadHashAfter = Encryption.ComputeSHA3(Encoding.ASCII.GetBytes(serializedpayload));
            var sigVerify = Encryption.Verify(payloadHashAfter, deserializedOutput.payloadSignature.signature, "sample/publicReal");
            Console.WriteLine($"Payload Signature verified? {sigVerify}");
            
            var encFileHash = Encryption.ComputeSHA3(encryptedFile);
            var postVerify = Encryption.Verify(encFileHash, deserializedOutput.payload.postSignature.signature, "sample/publicReal");
            var decryptedKey = Encryption.DecryptKey(encKey, "sample/privateReal", "sample_password");
            var decryptedFileAfter = Encryption.CipherFile(false, encryptedFile, decryptedKey);
            var decryptedHash = Encryption.ComputeSHA3(decryptedFileAfter);
            var preVerify = Encryption.Verify(decryptedHash, payload.preSignature.signature, "sample/publicReal");
            Console.WriteLine($"Post signature verified? {postVerify}");
            Console.WriteLine($"Pre signature verified? {preVerify}");
            Console.ReadLine();
        }

        static Keybase.DiscoverResponse.Match SelectUser(string user) {
            var response = Keybase.API.Discover(user);
            if(response.status.code != 0) { return null; }
            if(response.matches.Count == 0) {
                Console.WriteLine($"Unable to find {user}!");
                return null;
            } else if(response.matches.Count == 1) {
                Console.WriteLine($"One match found for {user}");
                Console.WriteLine(response.matches.First());
                Console.WriteLine("Is this correct? [yN]");
                var isCorrect = Console.ReadLine();
                if(isCorrect == "") { isCorrect = "n"; }
                if(isCorrect == "y") {
                    return response.matches.First();
                } else {
                    return null;
                }
            } else {
                Console.WriteLine("Select the correct user:");
                Console.WriteLine("0) None");
                var idx = 1;
                foreach(var match in response.matches) {
                   Console.Write($"{idx++})");
                   Console.WriteLine(match);
                }
                int userSelection;
                if(!Int32.TryParse(Console.ReadLine(), out userSelection) || userSelection > response.matches.Count) {
                    userSelection = 0;
                }
                if(userSelection == 0) {
                    return null;
                }
                return response.matches.ElementAt(userSelection - 1);
            }
        }
        
        // From http://stackoverflow.com/a/3404522
        static string ReadPassword(string keyFile) {
            string pass = "";
            Console.Write($"Enter your password for keyfile {keyFile}: ");
            ConsoleKeyInfo key;

            do
            {
                key = Console.ReadKey(true);

                
                // Backspace Should Not Work
                if (key.Key != ConsoleKey.Backspace && key.Key != ConsoleKey.Enter)
                {
                    pass += key.KeyChar;
                    Console.Write("*");
                }
                else
                {
                    if (key.Key == ConsoleKey.Backspace && pass.Length > 0)
                    {
                        pass = pass.Substring(0, (pass.Length - 1));
                        Console.Write("\b \b");
                    }
                }
            }
            // Stops Receving Keys Once Enter is Pressed
            while (key.Key != ConsoleKey.Enter);
            Console.WriteLine();
            return pass;
        }
    }
}
