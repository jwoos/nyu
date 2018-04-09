from flask import Flask
from flask.json import jsonify
from werkzeug.exceptions import HTTPException, default_exceptions
from flask.views import MethodView


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


class DefaultView(MethodView):
    def get(self):
        return jsonify({'status': 'okay'}), 200


view = DefaultView.as_view('default')
app.add_url_rule('/', view_func=view, methods=['GET'])
