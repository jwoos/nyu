using System;
using System.Collections.Generic;
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
                public class DNSProof
                {
                    public string domain { get; set; }
                    public string protocol { get; set; }
                    public string searchable { get; set; }
                }
                public List<DNSProof> dns { get; set; }
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
            public long ctime { get; set; }
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
            public class KeyEntry {
                public class PrimaryKey {
                    public string kid { get; set; }
                    public string key_type { get; set; }
                    public string bundle { get; set; }
                }
                public PrimaryKey primary { get; set; }
            }
            public string id { get; set; }
            public Basics basics { get; set; }
            public KeyEntry public_keys { get; set; }

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
            return client.Get<DiscoverResponse>(request).Data;
        }
        public static LookupResponse Lookup(string username)
        {
            var client = new RestClient("https://keybase.io/_/api/1.0/");
            var request = new RestRequest("user/lookup.json");
            request.AddParameter("usernames", username);
            request.AddParameter("fields", "basics,public_keys");
            foreach(var source in sources) {
                request.AddParameter(source, username);
            }
            return client.Get<LookupResponse>(request).Data;
        }
    }
}