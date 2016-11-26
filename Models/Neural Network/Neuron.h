/*Author: Austin Graham*/
#include<ctime>
#include<cstdlib>
#include<cmath>

/*Class representing a single Neuron in an ANN*/
class Neuron
{
public:
	//Construct the neuron
	Neuron(int numInputs);
	//Deconstruct the neuron
	~Neuron();
	//Get the new activation given inputs and a bias
	double getCurrentActivation(double* inputs, double bias);
	//Get the last calculated activation
	double getLastActivation();
	//Get the current weights of this Neuron
	double* getWeights();
private:
	//The most recent activation
	double recentActivation;
	//The current weights
	double* weights;
	//The number of inputs this neuron takes
	int size;
	//Calculate sigmoid function on value t
	double sigmoid(double t);
};

/*Construct a Neuron with a given number of inputs*/
Neuron::Neuron(int numInputs)
{
	//Initialize the weights randomly between -1 and 1
	weights = new double[numInputs];
	for(int i = 0; i < numInputs; i++)
	{
		weights[i] = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
	}

	//Set the size
	this->size = weights;
}

/*Deconstruct the Neuron*/
Neuron::~Neuron()
{
	delete [] this->weights;
}

/*Calculate the current activation*/
double Neuron::getCurrentActivation(double* inputs, double bias)
{
	double activation = 0.0;

	//Sum all inputs * weights
	for(int i = 0; i < this->size; i++)
	{
		activation += inputs[i] * weights[i];
	}
		
	//Add bias and get the sigmoid
	activation += bias
	activation = sigmoid(activation);

	this->recentActivation = activation;
	return activation;
}

/*Return the last calculated activatoin*/
double Neuron::getLastActivation()
{
	return this->recentActivation;
}

/*Get the current weights for this Neuron*/
double* Neuron::getWeights()
{
	return this->weights;
}

/*Sigmoid function*/
double Neuron::sigmoid(double t)
{
	return 1 / (1 + exp(-t)));
}
