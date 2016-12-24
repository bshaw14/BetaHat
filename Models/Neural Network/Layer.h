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
	void adjust();
protected:
	LinkedList<Neuron>* neurons;
	int size;
	double bias;
	double* savedDeltas;
	int inputSize;
	static Random* r;
private:
	double learningConstant;
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

void Layer::adjust()
{
	for(int i = 0; i < this->size; i++)
	{
		for(int j = 0; j < this->inputSize; j++)
		{
			(*this->neurons)[i].getWeights()[j] += learningConstant * savedDeltas[i*this->inputSize + j];
		}
	}
}
#endif
