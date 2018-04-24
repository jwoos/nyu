import logging

from flask.json import jsonify
from flask.views import MethodView
from flask import request
import pymysql

from src.db import connection
from src import auth, password, errors


logger = logging.getLogger(__name__)


class AccountView(MethodView):
    def post(self):
        body = request.get_json()

        if not body:
            return jsonify({'error': errors.DATA_EMPTY}), 422

        for k in ('email', 'password', 'class'):
            if not body.get(k):
                return jsonify({'error': errors.FIELD_EMPTY.format(k)}), 422

        body['password'] = password.generate(body['password'])

        if body['class'] == 'student':
            for k in ('university_number',):
                if not body.get(k):
                    return jsonify({'error': errors.FIELD_EMPTY.format(k)}), 422
        elif body['class'] == 'professor':
            for k in ('first_name', 'last_name'):
                if not body.get(k):
                    return jsonify({'error': errors.FIELD_EMPTY.format(k)}), 422
        else:
            return jsonify({'error': errors.FIELD_INVALID.format('class')}), 422


        try:
            connection.begin()
            with connection.cursor() as cursor:
                cursor.execute('INSERT INTO accounts (class, email, password) VALUES (%(class)s, %(email)s, %(password)s)', body)
                body['account_id'] = cursor.lastrowid

                if body['class'] == 'student':
                    cursor.execute('INSERT INTO students (account_id, university_number) VALUES (%(account_id)s, %(university_number)s)', body)
                else:
                    cursor.execute('INSERT INTO professors (account_id, first_name, last_name) VALUES (%(account_id)s, %(first_name)s, %(last_name)s)', body)

            connection.commit()

            return jsonify(None), 201
        except pymysql.err.IntegrityError as e:
            connection.rollback()
            logger.error(e)
            return jsonify({'error': errors.DATA_SAVE}), 500


class AccountAuthenticationView(MethodView):
    def get(self):
        token = request.headers.get('Authorization')
        try:
            account = check(token)
        except errors.AuthenticationError():
            return jsonify({'error': errors.AUTHENTICATION_INVALID}), 401

        return jsonify({'data': {'token': token, 'account': account}}), 200

    def post(self):
        body = request.get_json()

        if not body:
            return jsonify({'error': errors.DATA_EMPTY}), 422

        try:
            with connection.cursor() as cursor:
                cursor.execute('SELECT * FROM accounts WHERE email=%(email)s', body)

                account = cursor.fetchone()

                if account is None or not password.check(body['password'], account['password']):
                    return jsonify({'error': errors.AUTHENTICATION_WRONG}), 422

                if account['class'] == 'student':
                    cursor.execute('SELECT * FROM students WHERE account_id=%(id)s', account)
                else:
                    cursor.execute('SELECT * FROM professor WHERE account_id=%(id)s', account)

                user = cursor.fetchone()
                logging.debug(user)

                account.update(user)

                for k in ('password', 'created', 'updated', 'exp'):
                    if k in account:
                        del account[k]

                return jsonify({'data': {'token': auth.generate(account), 'account': account}}), 200
        except pymysql.err.IntegrityError as e:
            logger.error(e)
            return jsonify({'error': errors.DATA_SAVE}), 500
