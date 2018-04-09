from flask.json import jsonify
from flask.views import MethodView


class DefaultView(MethodView):
    def get(self):
        return jsonify({'status': 'okay'}), 200
