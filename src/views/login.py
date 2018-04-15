from flask.json import jsonify
from flask.views import MethodView
from flask import request

from src.db import connection
from src.errors import DATA_EMPTY
from src import password


class LoginView(MethodView):
    def post(self):
        body = request.get_json()

        if not body:
            return jsonify({'error': DATA_EMPTY}), 403

        with connection.cursor() as cursor:
            cursor.execute('SELECT * FROM accounts WHERE email=%(email)s', body)

            try:
                user = cursor.fetchone()
            except:
                return None, 403

            if user is None:
                return None, 403

            if not password.check(body['password'], user['password']):
                return None, 403

            return None, 200
