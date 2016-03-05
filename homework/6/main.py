from flask import Flask, request, render_template, redirect, url_for
import login

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/', methods=['POST'])
def login_user():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        error = login.validate(username, password)
        if (error):
            return error
        else:
            return ''

@app.route('/user')
def user():
    return render_template('logged.html')

if __name__ == '__main__':
    app.run(host='0.0.0.0', debug=True)
