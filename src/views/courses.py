import logging

from flask import request
from flask.json import jsonify
from flask.views import MethodView

from src.db import connection


logger = logging.getLogger(__name__)


class CourseView(MethodView):
    def get(self, course_id=None):
        with connection.cursor() as cursor:
            if course_id is None:
                # all
                cursor.execute('SELECT * FROM courses')
                return jsonify({'data': cursor.fetchall()}), 200
            else:
                # singular
                cursor.execute('SELECT * FROM courses WHERE id=%(id)s', {'id': course_id})
                return jsonify({'data': cursor.fetchone()}), 200

    def post(self):
        body = request.get_json()

        if not body:
            return jsonify({'error': DATA_EMPTY}), 422

        for k in ('name','description','professor_id'):
            if not body.get(k):
                return jsonify({'error': FIELD_EMPTY.format(k)})


        try:
            with connection.cursor() as cursor:
                cursor.execute('INSERT INTO courses (professor_id, name, description) VALUES (%(professor_id)s, %(name)s, %(description)s)', body)

            connection.commit()

            return jsonify(None), 201
        except pymysql.err.IntegrityError:
            logger.error(e)
            return jsonify({'error': DATA_SAVE}), 500


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

            return jsonify({'data': cursor.fetchall()}), 200
