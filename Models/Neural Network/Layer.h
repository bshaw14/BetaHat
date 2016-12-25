#ifndef LAYER_H
#define LAYER_H
#include"Neuron.h"
#include"../../Structures/LinkedList.h"
#include"../../random.h"
#include<iostream>
using namespace std;

class Layer
{
public:
	Layer(int size, int prevLayerSize);
	~Layer();
	int getSize();
	double* feed(double* activations);
	Neuron& operator[](int index);
	void adjust(Layer* prevLayer);
	void adjustWithInputs(double* inputs);
protected:
	LinkedList<Neuron>* neurons;
	int size;
	double* biases;
	double* savedDeltas;
	int inputSize;
	static Random* r;
	double learningConstant;
};

Random* Layer::r = new Random();

Layer::Layer(int size, int prevLayerSize)
{
	this->neurons = new LinkedList<Neuron>();
	this->size = size;
	this->inputSize = prevLayerSize;
	this->biases = new double[size];
	for(int i = 0; i < this->size; i++)
	{
		this->neurons->add(new Neuron(prevLayerSize));
		this->biases[i] = r->random_num(-1.0, 1.0);
	}
	this->savedDeltas = new double[size];
	this->learningConstant = 1.0;
}

Layer::~Layer()
{
	delete [] savedDeltas;
	delete neurons;
}

double* Layer::feed(double* prevActivations)
{
	double* layerActivations = new double[this->size];
	for(int i = 0; i < this->neurons->getLength(); i++)
	{
		layerActivations[i] = (*this->neurons)[i].getCurrentActivation(prevActivations, this->biases[i]);
	}
	return layerActivations;
}

int Layer::getSize()
{
	return this->size;
}

Neuron& Layer::operator[](int index)
{
	return (*neurons)[index];
}

void Layer::adjust(Layer* prevLayer)
{
	for(int i = 0; i < this->size; i++)
	{
		for(int j = 0; j < this->inputSize; j++)
		{
			(*this->neurons)[i].getWeights()[j] -= learningConstant * savedDeltas[i] * (*prevLayer)[j].getLastActivation();
		}
	}
}

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
