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
        [clipr.NamedArgument('m', "meta", Description = "The meta file for validation")]
        public string metaFile { get; set; }
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
            if(options.metaFile == null) {
                EncryptFile(options);
            } else {
                DecryptFile(options);
            }
            Console.ReadLine();
        }

        public static void EncryptFile(Options options) 
        {
            // Check the required parameters
            if(String.IsNullOrWhiteSpace(options.inFile) || !File.Exists(options.inFile)) {
                Console.WriteLine("Must specify an input file which exists");
                return;
            }
            if(String.IsNullOrWhiteSpace(options.keyFile) || !File.Exists(options.keyFile)) {
                Console.WriteLine("Must specify a key file which exists");
                return;
            }
            if(String.IsNullOrWhiteSpace(options.keybaseUsername)) {
                Console.WriteLine("Must specify a valid keybase user");
            }
            if(String.IsNullOrWhiteSpace(options.outFile)) {
                Console.WriteLine("Must specify an output file"); 
                return;
            }
            if(File.Exists(options.outFile)) {
                Console.WriteLine("Output file already exists!");
                return;
            }
            if(File.Exists(options.outFile + ".meta")) {
                Console.WriteLine("Metafile already exists!");
                return;
            }

            // Fetch keybase info
            var keybaseUser = Keybase.API.Lookup(options.keybaseUsername);
            if(keybaseUser == null) {
                Console.WriteLine("Must specify a valid keybase user");
                return;
            }

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

            if(payload.recipients.Count == 0) {
                Console.WriteLine("Warning: No valid recipients");
            }
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
            // Write out the meta file
            File.WriteAllText(outMeta, outputJSON);
        }

        public static void DecryptFile(Options options)
        {
            // Check the required parameters
            if(String.IsNullOrWhiteSpace(options.inFile) || !File.Exists(options.inFile)) {
                Console.WriteLine("Must specify an input encrypted file");
                return;
            }
            if(String.IsNullOrWhiteSpace(options.metaFile) || !File.Exists(options.metaFile)) {
                Console.WriteLine("Must specify a meta file which exists to decrypt");
                return;
            }
            if(String.IsNullOrWhiteSpace(options.keyFile) || !File.Exists(options.keyFile)) {
                Console.WriteLine("Must specify a key file which exists");
                return;
            }
            if(String.IsNullOrWhiteSpace(options.keybaseUsername)) {
                Console.WriteLine("Must specify a valid keybase user");
            }
            if(String.IsNullOrWhiteSpace(options.outFile)) {
                Console.WriteLine("Must specify an output location for the decrypted file"); 
                return;
            }
            if(File.Exists(options.outFile)) {
                Console.WriteLine("Output file already exists!");
                return;
            }

            // Fetch my keybase user
            var keybaseUser = Keybase.API.Lookup(options.keybaseUsername);
            if(keybaseUser == null) {
                Console.WriteLine("Must specify a valid keybase user");
                return;
            }

            // Parse in the JSON from the meta
            var metaFile = Newtonsoft.Json.JsonConvert.DeserializeObject<Output>(File.ReadAllText(options.metaFile));
            
            // Fetch the sender keybase
            var sender = Keybase.API.Lookup(metaFile.payload.sender.keybaseUsername);
            if(sender == null || sender.them.Count == 0) {
                Console.WriteLine($"Metafile references sender {metaFile.payload.sender.keybaseUsername}, but no such user exists");
                return;
            }
            var senderKey = sender.them[0].public_keys.primary.bundle;

            var payloadSerialized = Newtonsoft.Json.JsonConvert.SerializeObject(metaFile.payload, Formatting.None);
            var payloadHash = Encryption.ComputeSHA3(Encoding.ASCII.GetBytes(payloadSerialized));

            // Validate the meta signature
            var payloadValidates = Encryption.Verify(payloadHash, metaFile.payloadSignature.signature, senderKey);
            if(!payloadValidates) {
                Console.WriteLine("Payload didn't validate correctly!  metafile may have been tampered with!");
                return;
            }

            // Check to make sure we're in the list of recipients
            Output.Payload.Party myPartyEntry;
            if(metaFile.payload.sender.keybaseUsername == options.keybaseUsername) {
                myPartyEntry = metaFile.payload.sender;
            } else {
                myPartyEntry = metaFile.payload.recipients.FirstOrDefault(kb => kb.keybaseUsername == options.keybaseUsername);
                if(myPartyEntry == null) {
                    Console.WriteLine($"The keybase username you specified ({options.keybaseUsername}) isn't the sender, nor in the list of recipients");
                    return;
                }
            }

            // Validate the encrypted file with the postSignature
            var encryptedBytes = File.ReadAllBytes(options.inFile);
            var encryptedHash = Encryption.ComputeSHA3(encryptedBytes);

            var encryptedValidates = Encryption.Verify(encryptedHash, metaFile.payload.postSignature.signature, senderKey);
            if(!encryptedValidates) {
                Console.WriteLine("Encrypted file didn't validate! It may have been tampered with, or you may have the incorrect file!");
                return;
            }

            // Decrypt the key
            var decryptedKey = Encryption.DecryptKey(myPartyEntry.encryptedKey, options.keyFile, ReadPassword(options.keyFile));
            
            // Decrypt the file
            var decryptedFile = Encryption.CipherFile(false, encryptedBytes, decryptedKey);
            
            // Validate the decrypted file
            var decryptedHash = Encryption.ComputeSHA3(decryptedFile);
            var decryptedValidates = Encryption.Verify(decryptedHash, metaFile.payload.preSignature.signature, senderKey);
            if(!decryptedValidates) {
                Console.WriteLine("Decrypted file didn't validate! It may have been tampered with!");
                return;
            }

            // Everything validated! Save the file to disk
            File.WriteAllBytes(options.outFile, decryptedFile);
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
