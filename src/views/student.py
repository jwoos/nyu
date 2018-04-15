from flask import request
from flask.json import jsonify
from flask.views import MethodView

from src.db import connection


class StudentView(MethodView):
    def get(self, student_id=None):
        with connection.cursor() as cursor:
            if student_id is None:
                # all
                cursor.execute('SELECT * FROM students')
                return jsonify(cursor.fetchall()), 200
            else:
                # singular
                cursor.execute('SELECT * FROM students WHERE id=%(id)s', {'id': student_id})
                return jsonify(cursor.fetchone()), 200


class StudentEnrollmentView(MethodView):
    def get(self, student_id):
        with connection.cursor() as cursor:
            # all
            cursor.execute(
                'SELECT * FROM enrollments WHERE student_id=%(student_id)s',
                {'student_id': student_id}
            )

            return jsonify(cursor.fetchall()), 200


class StudentEvaluationEview(MethodView):
    def get(self, student_id, evaluation_id=None):
        with connection.cursor() as cursor:
            # all
            cursor.execute(
                '''
                SELECT * FROM evaluations WHERE enrollment_id IN (
                    SELECT id FROM enrollment WHERE student_id=%(student_id)s
                )
                ''',
                {'student_id': student_id}
            )

            return jsonify(cursor.fetchall()), 200
