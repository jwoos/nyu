import logging


from flask.json import jsonify
from flask.views import MethodView
from flask import request
import pymysql

from src.db import connection
from src import auth, password, errors


logger = logging.getLogger(__name__)


# TODO create corresponding student/professor account
class AccountView(MethodView):
    def post(self):
        body = request.get_json()

        if not body:
            return jsonify({'error': DATA_EMPTY}), 403

        for k in ('email', 'password', 'class'):
            if not body.get(k):
                return jsonify({'error': FIELD_EMPTY.format(k)})

        body['password'] = generate(body['password'])

        try:
            with connection.cursor() as cursor:
                cursor.execute('INSERT INTO accounts (class, email, password) VALUES (%(class)s, %(email)s, %(password)s)', body)

            connection.commit()

            return None, 201
        except pymysql.err.IntegrityError as e:
            logger.error(e)
            return jsonify({'error': errors.DATA_SAVE}), 403

class AccountAuthenticationView(MethodView):
    def get(self):
        try:
            check(request.headers.get('Authorization'))
        except errors.AuthenticationError():
            return jsonify({'error': AUTHENTICATION_INVALID}), 401

        return jsonify({'data': 'okay'}), 200

    def post(self):
        body = request.get_json()

        if not body:
            return jsonify({'error': DATA_EMPTY}), 403

        try:
            with connection.cursor() as cursor:
                cursor.execute('SELECT * FROM accounts WHERE email=%(email)s', body)

                account = cursor.fetchone()
                logger.debug(account)

                if account is None or not password.check(body['password'], account['password']):
                    return jsonify({'error': errors.AUTHENTICATION_WRONG}), 403

                if account['class'] == 'student':
                    cursor.execute('SELECT * FROM students WHERE account_id=%(id)s', account)
                else:
                    cursor.execute('SELECT * FROM professor WHERE account_id=%(id)s', account)

                user = cursor.fetchone()
                logging.debug(user)

                account.update(user)

                for k in ('password', 'created', 'updated'):
                    del account[k]

                return jsonify({'data': auth.generate(account)}), 200
        except pymysql.err.IntegrityError as e:
            logger.error(e)
            return jsonify({'error': errors.DATA_SAVE}), 403
