from flask import Flask
from flask import request
from random import randint
import betahat

app = Flask(__name__)
models = dict()

@app.route('/add', methods=['GET'])
def add():
	id = randint(1,100000)
	if request.args.get('type') == 'nn':
		models[id] = betahat.NeuralNetwork([2,3,1], 3, id)
	return str(id)

@app.route('/info', methods=['Get'])
def info():
	currentModel = models[int(request.args.get('id'))]
	return str(currentModel.getSuccessRate())

if __name__ == '__main__':
	app.run(debug=True)
