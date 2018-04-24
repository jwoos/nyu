import logging

from flask import Flask
from flask.json import jsonify
from werkzeug.exceptions import HTTPException, default_exceptions

from src.views import default, evaluation, account, student, professor, enrollment
from src.db import connection


logging.basicConfig(
    format='[%(levelname)s <> name] %(message)s',
    level=logging.DEBUG
)
logger = logging.getLogger(__name__)


app = Flask(__name__)


def default_error_handler(error):
    code = getattr(error, 'code', None) or 500
    try:
        context = jsonify({
            'error': {
                'description': getattr(error, 'message', None) or getattr(error, 'description', None) or str(error),
                'code': code
            }
        })
    except:
        context = jsonify({
            'error': {
                'description': error.get_body(),
                'code': code,
            }
        })

    return context, code


for code, error in default_exceptions.items():
    app.register_error_handler(error, default_error_handler)


default_view = default.DefaultView.as_view('default')
app.add_url_rule('/', view_func=default_view, methods=['GET'])

account_view = account.AccountView.as_view('account')
app.add_url_rule('/accounts', view_func=account_view, methods=['POST'])

account_authentication_view = account.AccountAuthenticationView.as_view('account_authentication')
app.add_url_rule('/accounts/authentications', view_func=account_authentication_view, methods=['GET', 'POST'])

evaluation_view = evaluation.EvaluationView.as_view('evaluation')
app.add_url_rule('/evaluations', view_func=evaluation_view, methods=['POST'])

student_view = student.StudentView.as_view('student')
app.add_url_rule('/students', view_func=student_view, methods=['GET'])
app.add_url_rule('/students/<int:student_id>', view_func=student_view, methods=['GET'])

student_enrollment_view = student.StudentEnrollmentView.as_view('student_enrollment')
app.add_url_rule('/students/<int:student_id>/enrollments', view_func=student_enrollment_view, methods=['GET'])

student_evaluation_view = student.StudentEvaluationEview.as_view('student_evaluation')
app.add_url_rule('/students/<int:student_id>/evaluations', view_func=student_evaluation_view, methods=['GET'])

professor_view = professor.ProfessorView.as_view('professor')
app.add_url_rule('/professors', view_func=professor_view, methods=['GET'])
app.add_url_rule('/professors/<int:professor_id>', view_func=professor_view, methods=['GET'])

professor_course_view = professor.ProfessorCourseView.as_view('professor_course')
app.add_url_rule('/professors/<int:professor_id>/courses', view_func=professor_course_view, methods=['GET'])

professor_evaluation_view = professor.ProfessorEvaluationView.as_view('professor_evaluation')
app.add_url_rule('/professors/<int:professor_id>/evaluations', view_func=professor_course_view, methods=['GET'])

enrollment_view = enrollment.EnrollmentView.as_view('enrollment')
app.add_url_rule('/enrollments', view_func=enrollment_view, methods=['GET', 'POST'])
app.add_url_rule('/enrollments/<int:enrollment_id>', view_func=enrollment_view, methods=['GET'])
