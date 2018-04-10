from flask.json import jsonify
from flask.views import MethodView
from flask import request
from src.db import connection

class LoginView(MethodView):
    def get(self):
        body = request.get_json();
            with connection.cursor() as cursor:
        cursor.callproc('login_user',body['email'],body['pw']);
        data = cursor.fetchall();
        if len(data) == 1:
            return jsonify({'status': 'okay'}), 200
        else
            return jsonify({'status': 'not okay'}), 200
