from flask import Flask
from flask.json import jsonify
from werkzeug.exceptions import HTTPException, default_exceptions

from src.views import default, evaluation, login
from src.db import connection


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


login_view = login.LoginView.as_view('login')
app.add_url_rule('/login', view_func=login_view, methods=['POST'])

evaluation_view = evaluation.EvaluationView.as_view('evaluation')
app.add_url_rule('/evaluation', view_func=evaluation_view, methods=['POST'])
