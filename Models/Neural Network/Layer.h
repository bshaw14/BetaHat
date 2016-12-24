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
protected:
	LinkedList<Neuron>* neurons;
	int size;
	double bias;
	double* savedDeltas;
	int inputSize;
	static Random* r;
};

Random* Layer::r = new Random();

Layer::Layer(int size, int prevLayerSize)
{
	this->neurons = new LinkedList<Neuron>();
	this->size = size;
	this->inputSize = prevLayerSize;
	for(int i = 0; i < this->size; i++)
	{
		this->neurons->add(new Neuron(prevLayerSize));
	}
	this->bias = Layer::r->random_num(-1.0, 1.0);
	this->savedDeltas = new double[size * prevLayerSize];
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
		layerActivations[i] = (*this->neurons)[i].getCurrentActivation(prevActivations, this->bias);
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
#endif
