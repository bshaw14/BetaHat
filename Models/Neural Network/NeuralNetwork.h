/*Author: Austin Graham*/
#ifndef NN_H
#define NN_H
#include<iostream>
#include"OutputLayer.h"
#include"HiddenLayer.h"
#include"../../Structures/LinkedList.h"

using namespace std;

class NeuralNetwork
{
public:
	NeuralNetwork(int* layers, int numOfLayers);
	~NeuralNetwork();
	double* feedForward(double* inputs);
	void backPropogate(double* expectedOutputs);
	friend ostream& operator<<(ostream& os, const NeuralNetwork& nn)
	{
		os<<"\tNEURAL NETWORK"<<endl;
		os<<"LAYERS:"<<endl;
		for(int i = 0; i < nn.layers->getLength(); i++)
		{
			os<<(*nn.layers)[i]<<endl;
		}
		os<<(*nn.outputLayer)<<endl;
		return os;
	}
private:
	LinkedList<HiddenLayer>* layers;
	OutputLayer* outputLayer;
	int inputSize;	
};

NeuralNetwork::NeuralNetwork(int* layers, int numOfLayers)
{
	this->layers = new LinkedList<HiddenLayer>();
	this->inputSize = layers[0];
	for(int i = 1; i < numOfLayers - 1; i++)
	{
		this->layers->add(new HiddenLayer(layers[i], layers[i-1]));
	}
	this->outputLayer = new OutputLayer(layers[numOfLayers - 1], layers[numOfLayers - 2]);
}

NeuralNetwork::~NeuralNetwork()
{
	delete this->layers;
	delete this->outputLayer;
}

double* NeuralNetwork::feedForward(double* inputs)
{
	double* nextFeedInput = inputs;
	for(int i = 0; i < this->layers->getLength(); i++)
	{
		nextFeedInput = (*this->layers)[i].feed(nextFeedInput); 
	}
	nextFeedInput = (*outputLayer).feed(nextFeedInput);
	return nextFeedInput;
}

void NeuralNetwork::backPropogate(double* expectedOutputs)
{
	double* deltas = outputLayer->backPropogate(expectedOutputs);
	for(int i = 0; i< 3; i++)
	{
		cout<<deltas[i]<<endl;
	}
}
#endif
