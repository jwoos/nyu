from flask import request
from flask.json import jsonify
from flask.views import MethodView

from src.db import connection


class EvaluationView(MethodView):
    def get(self, evaluation_id=None):
        with connection.cursor() as cursor:
            if evaluation_id is None:
                cursor.execute('SELECT * FROM evaluations')
                return jsonify(cursor.fetchall()), 200
            else:
                cursor.execute('SELECT * FROM evaluations WHERE id=%(id)s', {'id': evaluation_id})
                return jsonify(cursor.fetchone()), 200

    def post(self):
        raise NotImplementedError()
