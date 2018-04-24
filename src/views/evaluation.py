import logging

import pymysql
from flask import request
from flask.json import jsonify
from flask.views import MethodView

from src.db import connection
from src.errors import DATA_EMPTY, FIELD_EMPTY, DATA_SAVE


logger = logging.getLogger(__name__)


class EvaluationView(MethodView):
    def get(self, evaluation_id=None):
        with connection.cursor() as cursor:
            if evaluation_id is None:
                cursor.execute('SELECT * FROM evaluations')
                return jsonify({'data': cursor.fetchall()}), 200
            else:
                cursor.execute('SELECT * FROM evaluations WHERE id=%(id)s', {'id': evaluation_id})
                return jsonify({'data': cursor.fetchone()}), 200

    def post(self):
        body = request.get_json()

        if not body:
            return jsonify({'error': DATA_EMPTY}), 422

        for k in ('enrollment_id', 'comments', 'rating'):
            if not body.get(k):
                return jsonify({'error': FIELD_EMPTY.format(k)}), 422

        try:
            with connection.cursor() as cursor:
                cursor.execute('INSERT INTO enrollments (student_id,course_id,year,semester,section) VALUES (%(student_id)s, %(course_id)s, %(year)s, %(semester)s, %(section)s)', body)

            connection.commit()
            return jsonify(None), 201

        except pymysql.err.IntegrityError as e:
            logger.error(e)
            return jsonify({'error': DATA_SAVE}), 500
