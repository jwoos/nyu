from flask import request
from flask.json import jsonify
from flask.views import MethodView

from src.db import connection


class EnrollmentView(MethodView):
    def get(self, enrollment_id=None):
        with connection.cursor() as cursor:
            if enrollment_id is None:
                # all
                cursor.execute('SELECT * FROM enrollments')
                return jsonify(cursor.fetchall()), 200
            else:
                # singular
                cursor.execute('SELECT * FROM enrollments WHERE id=%(id)s', {'id': enrollment_id})
                return jsonify(cursor.fetchone()), 200

    def post(self):
        raise NotImplementedError()

    def patch(self):
        raise NotImplementedError()

    def delete(self):
        raise NotImplementedError()
