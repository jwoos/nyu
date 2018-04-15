from flask.json import jsonify
from flask.views import MethodView
from flask import request

from src.db import connection
from src import password
from src.errors import DATA_EMPTY, FIELD_EMPTY, DATA_SAVE


# TODO create corresponding student/professor account
class RegisterView(MethodView):
    def post(self):
        body = request.get_json()

        if not body:
            return jsonify({'error': DATA_EMPTY}), 403

        for k in ('username', 'password', 'class'):
            if not body.get(k):
                return jsonify({'error': FIELD_EMPTY.format(k)})

        try:
            with connection.cursor() as cursor:
                cursor.execute('INSERT INTO accounts (class, email, password) VALUES (%(class)s, %(email)s, %(password)s)', body)

            connection.commit()

            return None, 201
        except pymysql.err.IntegrityError:
            return jsonify({'error': DATA_SAVE}), 403
