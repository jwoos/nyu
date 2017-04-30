using System;
using System.Collections.Generic;

namespace Park {
    public class Output {
        public class Signature {
            public string hashAlgorithm { get; set; }
            public string signatureAlgorithm { get; set; }
            public string signature { get; set; }
        }
        public class Payload {
            public class File {
                public string encryptionAlgorithm { get; set; }
                public string link { get; set; }
            }
            public class Party {
                public string keybaseUsername { get; set; }
                public string keyFingerprint { get; set; }
                public string encryptionAlgorithm { get; set; }
                public string encryptedKey { get; set; }
            }
            public Signature preSignature { get; set; }
            public Signature postSignature { get; set; }
            public File file { get; set; }
            public Party sender { get; set; }
            public List<Party> recipients { get; set; }
        }
        public Signature payloadSignature { get; set; }
        public Payload payload { get; set; }
    } 
}