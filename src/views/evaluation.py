from flask import request
from flask.json import jsonify
from flask.views import MethodView

from src.db import connection


class EvaluationView(MethodView):
    def post(self):
        data = request.get_json()

        with connection.cursor() as cursor:
            cursor.execute()

        return None, 201
