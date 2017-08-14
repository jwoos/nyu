import hashlib

#SHA1
EXPECTED_USERNAME = 'd033e22ae348aeb5660fc2140aec35850c4da997'
EXPECTED_PASSWORD = '534d99d49b7d729e2d95ad547281bee251c09e8c'

def validate(username, password):
    username_sha1 = hashlib.sha1(username.encode('utf8')).hexdigest()
    password_sha1 = hashlib.sha1(password.encode('utf8')).hexdigest()
    try:
        assert username_sha1 == EXPECTED_USERNAME
        assert password_sha1 == EXPECTED_PASSWORD
        return None
    except AssertionError:
        return 'Wrong username or password!'
