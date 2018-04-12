import hashlib
import base64

import bcrypt


def generate(password):
    return bcrypt.hashpw(
        base64.b64encode(hashlib.sha256(password.encode()).digest()),
        bcrypt.gensalt()
    )

def check(password, hashed):
    return bcrypt.checkpw(
        base64.b64encode(hashlib.sha256(password.encode()).digest()),
        hashed
    )
