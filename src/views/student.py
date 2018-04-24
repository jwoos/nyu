from flask import request
from flask.json import jsonify
from flask.views import MethodView

from src.db import connection
from src import auth, errors


class StudentView(MethodView):
    def get(self, student_id=None):
        # authentication
        token = request.headers.get('Authorization')
        try:
            account = auth.check(token)
            if account['class'] != 'administrator':
                return jsonify({'error': errors.AUTHENTICATION_FORBIDDEN}), 403
        except errors.AuthenticationError:
            return jsonify({'error': errors.AUTHENTICATION_INVALID}), 401

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
        # authentication
        token = request.headers.get('Authorization')
        try:
            account = auth.check(token)
            if account['class'] != 'student':
                return jsonify({'error': errors.AUTHENTICATION_FORBIDDEN}), 403
        except errors.AuthenticationError:
            return jsonify({'error': errors.AUTHENTICATION_INVALID}), 401

        year = request.args.get('year')
        semester = request.args.get('semester')

        with connection.cursor() as cursor:
            if year and semester:
                # by year and semester
                cursor.execute(
                    '''
                    SELECT * FROM enrollments
                        JOIN courses ON courses.id = enrollments.course_id
                        WHERE enrollments.student_id=%(student_id)s AND enrollments.year=%(year)s AND enrollments.semester=%(semester)s
                    ''',
                    {'student_id': student_id, 'year': year, 'semester': semester}
                )
            elif year:
                # by year
                cursor.execute(
                    '''
                    SELECT * FROM enrollments
                        JOIN courses ON courses.id = enrollments.course_id
                        WHERE enrollments.student_id=%(student_id)s AND enrollments.year=%(year)s
                    ''',
                    {'student_id': student_id, 'year': year}
                )
            else:
                # all
                cursor.execute(
                    '''
                    SELECT * FROM enrollments
                        JOIN courses ON courses.id = enrollments.course_id
                        WHERE enrollments.student_id=%(student_id)s
                    ''',
                    {'student_id': student_id}
                )

            return jsonify({'data': cursor.fetchall()}), 200


class StudentEvaluationEview(MethodView):
    def get(self, student_id, evaluation_id=None):
        # authentication
        token = request.headers.get('Authorization')
        try:
            account = auth.check(token)
            if account['class'] != 'student':
                return jsonify({'error': errors.AUTHENTICATION_FORBIDDEN}), 403
        except errors.AuthenticationError:
            return jsonify({'error': errors.AUTHENTICATION_INVALID}), 401

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
                        SELECT id FROM enrollments WHERE student_id=%(student_id)s
                    )
                    ''',
                    args
                )

            return jsonify({'data': cursor.fetchall()}), 200
