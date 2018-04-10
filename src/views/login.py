from flask.json import jsonify
from flask.views import MethodView
from flask import request
from src.db import connection

class LoginView(MethodView):
    def post(self):
        body = request.get_json();

        if not body:
            return jsonify({}), 400

        with connection.cursor() as cursor:
            cursor.execute("SELECT email, password FROM accounts WHERE email=%(email)s AND password=%(pw)s", body);
            rows = cursor.fetchall();
            if len(rows) == 0:
                return jsonify({'status': 'not okay'}), 403
            elif len(data) == 1:
                return jsonify({'status': 'okay'}), 200
            else:
                return jsonify({'status': 'not okay'}), 403
