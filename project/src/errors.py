DATA_SAVE = 'Error saving data'
DATA_EMPTY = 'Data cannot be empty'
FIELD_EMPTY = '{} cannot be empty'
FILED_INVALID = '{} has an invalid value'
AUTHENTICATION_WRONG = 'Email or password was wrong'
AUTHENTICATION_INVALID = 'Invalid authentication'
AUTHENTICATION_FORBIDDEN = 'Forbidden'


class AuthenticationError(Exception):
    pass
