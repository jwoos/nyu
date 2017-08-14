using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using RestSharp;

namespace Keybase
{
    public class Status 
    {
        public int code { get; set; }
        public string name { get; set; }
    }
    public class DiscoverResponse
    {
        public class Match
        {
            public class Key {
                public string key_fingerprint { get; set; }
                public int bits { get; set; }
                public int algo { get; set; }
            }
            public class RemoteProofs {
                public string twitter { get; set; }
                public string github { get; set; }
                public string reddit { get; set; }
                public string hackernews { get; set; }
                public string coinbase { get; set; }
                public string facebook { get; set; }
            }
            public string username { get; set; }
            public string uid { get; set; }
            public Key public_key { get; set; }
            public string full_name { get; set; }
            public RemoteProofs remote_proofs { get; set; }

            public override string ToString() {
                return $"{full_name}\n" +
                       (!String.IsNullOrWhiteSpace(remote_proofs.twitter)  ? $"  twitter:  @{remote_proofs.twitter}\n" : "") +
                       (!String.IsNullOrWhiteSpace(remote_proofs.github)   ? $"  github:   {remote_proofs.github}\n" : "") +
                       (!String.IsNullOrWhiteSpace(remote_proofs.reddit)   ? $"  reddit:   /u/{remote_proofs.reddit}\n" : "") +
                       (!String.IsNullOrWhiteSpace(remote_proofs.facebook) ? $"  facebook: {remote_proofs.facebook}\n" : "");
            }
        }
        public Status status { get; set; }
        public List<Match> matches { get; set; }
    }
    public class LookupResponse
    {
        public class Entry {
            public class Basics {
                public string username { get; set; }
                public string salt { get; set; }
            }
            public class Profile {
                public string full_name { get; set; }
            }
            public class KeyEntry {
                public class PrimaryKey {
                    public string kid { get; set; }
                    public string key_type { get; set; }
                    public string bundle { get; set; }
                    public string key_fingerprint { get; set; }
                    public int key_bits { get; set; }
                    public int key_algo { get; set; }
                }
                public PrimaryKey primary { get; set; }
            }
            public class RemoteProofs {
                public class Proof {
                    public string proof_type { get; set; }
                    public string nametag { get; set; }
                }
                public List<Proof> all { get; set; }
            }
            public string id { get; set; }
            public Basics basics { get; set; }
            public Profile profile { get; set; }
            public KeyEntry public_keys { get; set; }
            public RemoteProofs proofs_summary { get; set; }

        }
        public Status status { get; set; }
        public List<Entry> them { get; set; }
    }
    public static class API
    {
        public static string[] sources = new string[] { "twitter", "github", "hackernews", "web" };
        public static DiscoverResponse Discover(string name)
        {
            var client = new RestClient("https://keybase.io/_/api/1.0/");
            var request = new RestRequest("user/discover.json");
            request.AddParameter("flatten", 1);
            foreach(var source in sources) {
                request.AddParameter(source, name);
            }
            var discovered = client.Get<DiscoverResponse>(request).Data;

            // HACK: make a separate request for the user itself, just in case
            var lookedUp = Lookup(name);
            if(lookedUp.status.code == 0 && lookedUp.them.Count > 0) {
                var them = lookedUp.them.First();
                if(!discovered.matches.Any(x => x.uid == them.id)) {
                    var spoofedDiscover = new DiscoverResponse.Match {
                        username = name,
                        uid = them.id,
                        public_key = new DiscoverResponse.Match.Key {
                            key_fingerprint = them.public_keys.primary.key_fingerprint,
                            bits = them.public_keys.primary.key_bits,
                            algo = them.public_keys.primary.key_algo
                        },
                        full_name = them.profile.full_name,
                        remote_proofs = new DiscoverResponse.Match.RemoteProofs {
                            twitter = them.proofs_summary.all.FirstOrDefault(x => x.proof_type == "twitter")?.nametag,
                            reddit = them.proofs_summary.all.FirstOrDefault(x => x.proof_type == "reddit")?.nametag,
                            facebook = them.proofs_summary.all.FirstOrDefault(x => x.proof_type == "facebook")?.nametag,
                            github = them.proofs_summary.all.FirstOrDefault(x => x.proof_type == "github")?.nametag,
                            hackernews = them.proofs_summary.all.FirstOrDefault(x => x.proof_type == "hackernews")?.nametag,
                            coinbase = them.proofs_summary.all.FirstOrDefault(x => x.proof_type == "coinbase")?.nametag
                        }
                    };
                    discovered.matches.Add(spoofedDiscover);
                }
            }
            
            return discovered;
        }
        public static LookupResponse Lookup(string username)
        {
            var client = new RestClient("https://keybase.io/_/api/1.0/");
            var request = new RestRequest("user/lookup.json");
            request.AddParameter("usernames", username);
            request.AddParameter("fields", "basics,public_keys,proofs_summary,profile");
            foreach(var source in sources) {
                request.AddParameter(source, username);
            }
            return client.Get<LookupResponse>(request).Data;
        }
    }
}