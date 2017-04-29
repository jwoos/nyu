using System;
using System.Linq;
using Keybase;

namespace Park
{
    class Program
    {
        static void Main(string[] args)
        {
            while(true) {
                Console.WriteLine("Enter a user to lookup");
                var user = Console.ReadLine();
                var selectedUser = SelectUser(user);
                if(selectedUser == null) {
                    continue;
                }
                var info = Keybase.API.Lookup(selectedUser.username);
                Console.WriteLine(info.them.First().public_keys.primary.bundle);
            }
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
    }
}
