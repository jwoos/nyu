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
            

            var realHash = Encryption.ComputeSHA3("sample/fileReal.txt");
            var fakeHash = Encryption.ComputeSHA3("sample/fileFake.txt");

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

            var key = Encryption.GenerateKey();
            Console.WriteLine($"Generated key: {key}");
            File.WriteAllBytes("out", Encryption.CipherFile(true, "sample/fileReal.txt", key));
            File.WriteAllBytes("dec", Encryption.CipherFile(false, "out", key));

            var encKey = Encryption.EncryptKeyFor(key, File.ReadAllText("sample/publicReal"));
            var decKey = Encryption.DecryptKey(encKey, "sample/privateReal", "sample_password");

            Console.WriteLine($"key == decrypt(encrypt(key))?  {key == decKey}");
            
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
