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
                return jsonify({'data': cursor.fetchall()}), 200
            else:
                # singular
                cursor.execute('SELECT * FROM professors WHERE id=%(id)s', {'id': professor_id})
                return jsonify({'data': cursor.fetchone()}), 200


class ProfessorCourseView(MethodView):
    def get(self, professor_id):
        with connection.cursor() as cursor:
            # all
            cursor.execute(
                'SELECT * FROM courses WHERE professor_id=%(professor_id)s',
                {'professor_id': professor_id}
            )

            return jsonify({'data': cursor.fetchall()}), 200


class ProfessorEvaluationView(MethodView):
    def get(self, professor_id):
        year = request.args.get('year')
        semester = request.args.get('semester')
        course_id = request.args.get('course_id')

        args = {
            'professor_id': professor_id,
            'year': year,
            'semester': semester,
            'course_id': course_id
        }

        with connection.cursor() as cursor:
            if course_id:
                if year and semester:
                    cursor.execute(
                        '''
                        SELECT * FROM evaluations WHERE enrollment_id IN (
                            SELECT enrollments.id FROM courses INNER JOIN enrollments ON courses.id = enrollments.course_id
                            WHERE courses.professor_id=%(professor_id)s AND enrollments.year=%(year)s AND enrollments.semester=%(semester)s AND courses.id=%(course_id)s
                        )
                        ''',
                        args
                    )
                elif year:
                    cursor.execute(
                        '''
                        SELECT * FROM evaluations WHERE enrollment_id IN (
                            SELECT enrollments.id FROM courses INNER JOIN enrollments ON courses.id = enrollments.course_id
                            WHERE courses.professor_id=%(professor_id)s AND enrollments.year=%(year)s AND courses.id=%(course_id)s
                        )
                        ''',
                        args
                    )
                else:
                    # all
                    cursor.execute(
                        '''
                        SELECT * FROM evaluations WHERE enrollment_id IN (
                            SELECT enrollments.id FROM courses INNER JOIN enrollments ON courses.id = enrollments.course_id
                            WHERE courses.professor_id=%(professor_id)s AND courses.id=%(course_id)s
                        )
                        ''',
                        args
                    )
            else:
                if year and semester:
                    cursor.execute(
                        '''
                        SELECT * FROM evaluations WHERE enrollment_id IN (
                            SELECT enrollments.id FROM courses INNER JOIN enrollments ON courses.id = enrollments.course_id
                            WHERE courses.professor_id=%(professor_id)s AND enrollments.year=%(year)s AND enrollments.semester=%(semester)s
                        )
                        ''',
                        args
                    )
                elif year:
                    cursor.execute(
                        '''
                        SELECT * FROM evaluations WHERE enrollment_id IN (
                            SELECT enrollments.id FROM courses INNER JOIN enrollments ON courses.id = enrollments.course_id
                            WHERE courses.professor_id=%(professor_id)s AND enrollments.year=%(year)s
                        )
                        ''',
                        args
                    )
                else:
                    # all
                    cursor.execute(
                        '''
                        SELECT * FROM evaluations WHERE enrollment_id IN (
                            SELECT enrollments.id FROM courses INNER JOIN enrollments ON courses.id = enrollments.course_id
                            WHERE courses.professor_id=%(professor_id)s
                        )
                        ''',
                        args
                    )

            return jsonify({'data': cursor.fetchall()}), 200
