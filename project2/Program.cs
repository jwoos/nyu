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
        [clipr.NamedArgument('o', "out", Description = "The output for the encrypted file")]
        public string outFile { get; set; }
        [clipr.NamedArgument('u', "username", Description = "Your Keybase Username")]
        public string keybaseUsername { get; set; }
        [clipr.NamedArgument('k', "key", Description = "The private key used for signing")]
        public string keyFile { get; set; }
        [clipr.NamedArgument('r', "recipient", Description = "Keybase usernames of any recipients who should be able to access the file", Action = clipr.ParseAction.Append)]
        public List<string> recipients { get; set; }
    }

    class Program
    {
        static void Main(string[] args)
        {
            var options = CliParser.Parse<Options>(args);
            
            // Fetch keybase info
            var keybaseUser = Keybase.API.Lookup(options.keybaseUsername);
            var kbFingerprint = keybaseUser.them[0].public_keys.primary.key_fingerprint;
            var fileFingerprint = Encryption.GetKeyFingerprint(options.keyFile);
            if(kbFingerprint != fileFingerprint) {
                Console.WriteLine($"Invalid! {options.keyFile} is not the private key for keybase user {options.keybaseUsername}!");
                Console.WriteLine($"Fingerprints don't match.  Keybase: {kbFingerprint} vs File: {fileFingerprint}");
                Console.ReadLine();
                return;
            }

            var recipients = 
                from recipient in options.recipients
                let kb = SelectUser(recipient)
                where kb != null
                select Keybase.API.Lookup(kb.username);

            // Read in the file
            var fileBytes = File.ReadAllBytes(options.inFile);
            var fileHash = Encryption.ComputeSHA3(fileBytes);

            var keyPassword = ReadPassword(options.keyFile);
            var preSignature = Encryption.Sign(fileHash, options.keyFile, keyPassword);

            // Generate the encryption key and encrypt the file
            var key = Encryption.GenerateKey();
            var encryptedFile = Encryption.CipherFile(true, fileBytes, key);
            File.WriteAllBytes(options.outFile, encryptedFile);

            // Sign the encrypted file as well
            var hashOfEncrypted = Encryption.ComputeSHA3(encryptedFile);
            var signatureForEncrypted = Encryption.Sign(hashOfEncrypted, options.keyFile, keyPassword);

            var keyEncryptedForSelf = Encryption.EncryptKeyFor(key, keybaseUser.them[0].public_keys.primary.bundle);

            var partyObjects = 
                from recipient in recipients
                let encryptedKey = Encryption.EncryptKeyFor(key, recipient.them[0].public_keys.primary.bundle)
                select new Output.Payload.Party { 
                    keybaseUsername = recipient.them[0].basics.username,
                    keyFingerprint = recipient.them[0].public_keys.primary.key_fingerprint,
                    encryptionAlgorithm = "PGP RsaGeneral",
                    encryptedKey = encryptedKey 
                  };

            var payload = new Output.Payload {
                sender = new Output.Payload.Party {
                    keybaseUsername = options.keybaseUsername,
                    keyFingerprint = keybaseUser.them[0].public_keys.primary.key_fingerprint,
                    encryptionAlgorithm = "PGP RsaGeneral",
                    encryptedKey = keyEncryptedForSelf,
                },
                recipients = partyObjects.ToList(),
                preSignature = new Output.Signature {
                    hashAlgorithm = "SHA3-384",
                    signatureAlgorithm = "PGP RsaGeneral Sha384",
                    signature = preSignature,
                },
                postSignature = new Output.Signature {
                    hashAlgorithm = "SHA3-384",
                    signatureAlgorithm = "PGP RsaGeneral Sha384",
                    signature = signatureForEncrypted
                }
            };
            var payloadJSON = Newtonsoft.Json.JsonConvert.SerializeObject(payload, Formatting.None);
            var payloadHash = Encryption.ComputeSHA3(Encoding.ASCII.GetBytes(payloadJSON));
            var payloadSignature = Encryption.Sign(payloadHash, options.keyFile, keyPassword);
            var output = new Output {
                payload = payload,
                
                payloadSignature = new Output.Signature {
                    hashAlgorithm = "SHA3-384",
                    signatureAlgorithm = "PGP RsaGeneral Sha384",
                    signature = payloadSignature
                },
                fileMeta = new Output.File {
                    encryptionAlgorithm = "AES/CTR/NoPadding",
                    link = "Unhosted (Update when uploaded)",
                }
            };

            var outputJSON = Newtonsoft.Json.JsonConvert.SerializeObject(output, Formatting.Indented);
            var outMeta = options.outFile + ".meta";
            File.WriteAllText(outMeta, outputJSON);
            // Write out the encrypted file

            /*
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
            */
        }

        static Keybase.DiscoverResponse.Match SelectUser(string user) {
            var response = Keybase.API.Discover(user);
            if(response.status.code != 0) { return null; }
            var validMatches = 
                from match in response.matches
                where match.public_key != null
                select match;
            if(response.matches.Count == 0) {
                Console.WriteLine($"Unable to find {user} with a valid public key!");
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
