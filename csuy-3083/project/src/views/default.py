from flask.json import jsonify
from flask.views import MethodView


class DefaultView(MethodView):
    def get(self):
        return jsonify({'data': {'status': 'okay'}}), 200
