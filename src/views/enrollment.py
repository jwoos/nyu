import pymysql
from flask import request
from flask.json import jsonify
from flask.views import MethodView

from src.db import connection
from src.errors import DATA_EMPTY, FIELD_EMPTY, DATA_SAVE


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
        body = request.get_json()

        if not body:
            return jsonify({'error': DATA_EMPTY}), 422

        for k in ('student_id', 'course_id', 'year', 'semester', 'section'):
            if not body.get(k):
                return jsonify({'error': FIELD_EMPTY.format(k)})

        try:
            with connection.cursor() as cursor:
                cursor.execute('INSERT INTO enrollments (student_id,course_id,year,semester,section) VALUES (%(student_id)s, %(course_id)s, %(year)s, %(semester)s, %(section)s)', body)

            connection.commit()
            return None, 201

        except pymysql.err.IntegrityError as e:
            print(e)
            return jsonify({'error': DATA_SAVE}), 500
