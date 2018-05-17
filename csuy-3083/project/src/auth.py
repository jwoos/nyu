import datetime
import logging
import os

import jwt

from src import password, errors


logger = logging.getLogger(__name__)


SECRET = os.getenv('APP_SECRET')


def check(token):
    if token is None:
        raise errors.AuthenticationError()

    try:
        payload =  jwt.decode(token.encode(), SECRET, algorithm='HS256')
        return payload
    except (jwt.exceptions.InvalidTokenError, jwt.exceptions.DecodeError, jwt.exceptions.ExpiredSignatureError) as e:
        logger.error(e)
        raise errors.AuthenticationError()

def generate(payload):
    payload['exp'] = datetime.datetime.utcnow() + datetime.timedelta(days=3)
    return jwt.encode(payload, SECRET, algorithm='HS256').decode()
