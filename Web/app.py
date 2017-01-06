from flask import Flask
from flask import request

app = Flask(__name__)

@app.route('/add', methods=['GET','POST'])
def add():
	a = request.args.get('a')
	b = request.args.get('b')
	return a + b

if __name__ == '__main__':
	app.run(debug=True)
