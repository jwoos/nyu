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
                return jsonify({'data': cursor.fetchall()}), 200
            else:
                # singular
                cursor.execute('SELECT * FROM students WHERE id=%(id)s', {'id': student_id})
                return jsonify({'data': cursor.fetchone()}), 200


class StudentEnrollmentView(MethodView):
    def get(self, student_id):
        year = request.args.get('year')
        semester = request.args.get('semester')

        with connection.cursor() as cursor:
            if year and semester:
                # by year and semester
                cursor.execute(
                    'SELECT * FROM enrollments WHERE student_id=%(student_id)s AND year=%(year)s AND semester=%(semester)s',
                    {'student_id': student_id, 'year': year, 'semester': semester}
                )
            elif year:
                # by year
                cursor.execute(
                    'SELECT * FROM enrollments WHERE student_id=%(student_id)s AND year=%(year)s',
                    {'student_id': student_id, 'year': year}
                )
            else:
                # all
                cursor.execute(
                    'SELECT * FROM enrollments WHERE student_id=%(student_id)s',
                    {'student_id': student_id}
                )

            return jsonify({'data': cursor.fetchall()}), 200


class StudentEvaluationEview(MethodView):
    def get(self, student_id, evaluation_id=None):
        year = request.args.get('year')
        semester = request.args.get('semester')

        args = {
            'student_id': student_id,
            'year': year,
            'semester': semester
        }

        with connection.cursor() as cursor:
            if year and semester:
                # by year and semester
                cursor.execute(
                    '''
                    SELECT * FROM evaluations WHERE enrollment_id IN (
                        SELECT * FROM enrollments WHERE student_id=%(student_id)s AND year=%(year)s AND semester=%(semester)s
                    )
                    ''',
                    args
                )
            elif year:
                # by year
                cursor.execute(
                    '''
                    SELECT * FROM evaluations WHERE enrollment_id IN (
                        SELECT * FROM enrollments WHERE student_id=%(student_id)s AND year=%(year)s
                    )
                    ''',
                    args
                )
            else:
                # all
                cursor.execute(
                    '''
                    SELECT * FROM evaluations WHERE enrollment_id IN (
                        SELECT id FROM enrollment WHERE student_id=%(student_id)s
                    )
                    ''',
                    args
                )

            return jsonify({'data': cursor.fetchall()}), 200
