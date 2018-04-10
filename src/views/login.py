from flask.json import jsonify
from flask.views import MethodView
from flask import request
from src.db import connection

class LoginView(MethodView):
    def get(self):
        body = request.get_json();
        with connection.cursor() as cursor:
            cursor.execute("SELECT email, password FROM accounts WHERE email=? AND password=?",(body['email'],body['pw']));
            rows = cursor.fetchall();
            if len(rows) == 0:
                return jsonify({'status': 'not okay'}), 403
            elif len(data) == 1:
                return jsonify({'status': 'okay'}), 200
            else
                return jsonify({'status': 'not okay'}), 403
