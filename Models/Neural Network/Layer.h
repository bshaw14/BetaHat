#ifndef LAYER_H
#define LAYER_H
#include"Neuron.h"
#include"../../Structures/LinkedList.h"
#include"../../random.h"
#include<iostream>
using namespace std;

/*Encapsulates a Layer object*/
class Layer
{
public:
	//Construct a layer give its size, and the input size
	//of each Neuron
	Layer(int size, int prevLayerSize);
	//Destroy the layer
	~Layer();
	//Get the number of neurons in this layer
	int getSize();
	//Feed input through the layer
	double* feed(double* activations);
	//Get a Neuron from the layer
	Neuron& operator[](int index);
	//Adjust the weights for each Neuron in the layer using 
	//previous deltas in back propogation
	void adjust(Layer* prevLayer);
	//Do the same as above, but use inputs
	void adjustWithInputs(double* inputs);
protected:
	//List of Neurons in this Layer
	LinkedList<Neuron>* neurons;
	//Number of neurons in this layer
	int size;
	//The biases for each Neuron in this layer
	double* biases;
	//The deltas of each Neuron in this layer
	double* savedDeltas;
	//The size of input for each Neuron in this layer
	int inputSize;
	//Random generator for biases
	static Random* r;
	//Rate at which the network should learn
	double learningConstant;
};

/*Random generator for biases*/
Random* Layer::r = new Random();

/*Construct the Layer object*/
Layer::Layer(int size, int prevLayerSize)
{
	//Create list of Neurons
	this->neurons = new LinkedList<Neuron>();
	//Set the size
	this->size = size;
	//Set the input size
	this->inputSize = prevLayerSize;
	//Create list of biases
	this->biases = new double[size];
	//Fill list of Neurons and biases
	for(int i = 0; i < this->size; i++)
	{
		this->neurons->add(new Neuron(prevLayerSize));
		this->biases[i] = r->random_num(-1.0, 1.0);
	}
	//Create list of deltas
	this->savedDeltas = new double[size];
	//Set the rate of learning to default
	this->learningConstant = 1.0;
}

/*Destroy Layer object*/
Layer::~Layer()
{
	//Destroy all dynamically allocated data
	delete [] savedDeltas;
	delete neurons;
}

/*Feed input through this Layer*/
double* Layer::feed(double* prevActivations)
{
	//Create list of new activations
	double* layerActivations = new double[this->size];
	//Get new activation of each Neuron
	for(int i = 0; i < this->neurons->getLength(); i++)
	{
		layerActivations[i] = (*this->neurons)[i].getCurrentActivation(prevActivations, this->biases[i]);
	}
	return layerActivations;
}

/*Get the number of Neurons in this layer*/
int Layer::getSize()
{
	return this->size;
}

/*Get a particular Neuron in this Layer*/
Neuron& Layer::operator[](int index)
{
	return (*neurons)[index];
}

/*Adjust weights of each neuron using activations of Neurons 
from previous Layer*/
void Layer::adjust(Layer* prevLayer)
{
	//For each Neuron
	for(int i = 0; i < this->size; i++)
	{
		//For each prev Neuron
		for(int j = 0; j < this->inputSize; j++)
		{
			(*this->neurons)[i].getWeights()[j] -= learningConstant * savedDeltas[i] * (*prevLayer)[j].getLastActivation();
		}
	}
}

/*Adjust wieghts above using inputs instead of Layer*/
void Layer::adjustWithInputs(double* inputs)
{
	for(int i = 0; i < this->size; i++)
	{
		for(int j = 0; j < this->inputSize; j++)
		{
			(*this->neurons)[i].getWeights()[j] -= learningConstant * savedDeltas[i] * inputs[j];
		}
	}
}
#endif
