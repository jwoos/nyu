from flask import request
from flask.json import jsonify
from flask.views import MethodView

from src.db import connection


class ProfessorView(MethodView):
    def get(self, professor_id=None):
        with connection.cursor() as cursor:
            if professor_id is None:
                # all
                cursor.execute('SELECT * FROM professors')
                return jsonify(cursor.fetchall()), 200
            else:
                # singular
                cursor.execute('SELECT * FROM professors WHERE id=%(id)s', {'id': professor_id})
                return jsonify(cursor.fetchone()), 200


class ProfessorCourseView(MethodView):
    def get(self, professor_id):
        with connection.cursor() as cursor:
            # all
            cursor.execute(
                'SELECT * FROM courses WHERE professor_id=%(professor_id)s',
                {'professor_id': professor_id}
            )

            return jsonify(cursor.fetchall()), 200


class ProfessorEvaluationView(MethodView):
    def get(self, professor_id):
        with connection.cursor() as cursor:
            # all
            cursor.execute(
                '''
                SELECT * FROM evaluations WHERE enrollment_id IN (
                    SELECT enrollments.id FROM courses INNER JOIN enrollments ON courses.id = enrollments.course_id
                    WHERE professor_id=%(professor_id)s
                )
                ''',
                {'professor_id': professor_id}
            )

            return jsonify(cursor.fetchall()), 200
