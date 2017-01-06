import betahat
import random

if __name__ == "__main__":
	print 'Building network...'
	nn = betahat.NeuralNetwork([2,3,1], 3, 199)
	print 'Constructing training data...'
	set = betahat.TrainingSet(2,1,100)
	for i in range(1,101):
		_input = [random.randint(0,1), random.randint(0,1)]
		_output = [_input[0] ^ _input[1]]
		set.addObservation(_input, _output)
	print 'Training...'
	nn.Train(1000, set)
	print 'Success Rate: ', 100 * nn.getSuccessRate(),'%'
	print 'Random test values:'
	for i in range(1,21):
		x = random.randint(0,1)
		y = random.randint(0,1)
		ans = nn.Classify([x,y])
		if ans[0] >= .5:
			ans[0] = 1
		else:
			ans[0] = 0
		print x, '^', y, '=', ans[0]
