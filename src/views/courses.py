from flask import request
from flask.json import jsonify
from flask.views import MethodView

from src.db import connection


class CourseView(MethodView):
    def get(self, course_id=None):
        with connection.cursor() as cursor:
            if course_id is None:
                # all
                cursor.execute('SELECT * FROM courses')
            else:
                # singular
                cursor.execute('SELECT * FROM courses WHERE id=%(id)s', {'id': course_id})

            return jsonify(cursor.fetchall()), 200

    def post(self):
        raise NotImplementedError()

    def patch(self):
        raise NotImplementedError()

    def delete(self):
        raise NotImplementedError()


class CourseEvaluationView(MethodView):
    def get(self, course_id):
        with connection.cursor() as cursor:
            cursor.execute(
                '''
                SELECT * FROM evaluations WHERE enrollment_id IN (
                    SELECT id FROM enrollments WHERE course_id=%(course_id)s
                )
                ''',
                {'course_id': course_id}
            )

            return jsonify(cursor.fetchall()), 200
