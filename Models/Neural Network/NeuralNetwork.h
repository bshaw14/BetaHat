/*Author: Austin Graham*/
#ifndef NN_H
#define NN_H
#include<iostream>
#include"OutputLayer.h"
#include"HiddenLayer.h"
#include"../../Structures/LinkedList.h"

using namespace std;

/*Encapsulates a Neural Network object*/
class NeuralNetwork
{
public:
	//Create the network with specified Layers
	NeuralNetwork(int* layers, int numOfLayers);
	//Destroy Network
	~NeuralNetwork();
	//Feed input through the network
	double* feedForward(double* inputs);
	//Perform back propogation for a set of inputs and outputs
	void backPropogate(double* expectedOutputs, double* inputs);
	//Display network information
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
	//Hidden layers in the network
	LinkedList<HiddenLayer>* layers;
	//The output layer
	OutputLayer* outputLayer;
	//Number of inputs for this network
	int inputSize;	
};

/*Construct a Neural Network*/
NeuralNetwork::NeuralNetwork(int* layers, int numOfLayers)
{
	//Create the list of layers and set the input size
	this->layers = new LinkedList<HiddenLayer>();
	this->inputSize = layers[0];
	//Fill the hidden layer list
	for(int i = 1; i < numOfLayers - 1; i++)
	{
		this->layers->add(new HiddenLayer(layers[i], layers[i-1]));
	}
	//create the output layer
	this->outputLayer = new OutputLayer(layers[numOfLayers - 1], layers[numOfLayers - 2]);
}

/*Destroy the network*/
NeuralNetwork::~NeuralNetwork()
{
	delete this->layers;
	delete this->outputLayer;
}

/*Feed input through the network*/
double* NeuralNetwork::feedForward(double* inputs)
{
	//Set the current feed to the inputs
	double* nextFeedInput = inputs;
	//Feed through each hidden layer
	for(int i = 0; i < this->layers->getLength(); i++)
	{
		nextFeedInput = (*this->layers)[i].feed(nextFeedInput); 
	}
	//Feed through the output layer
	nextFeedInput = (*outputLayer).feed(nextFeedInput);
	return nextFeedInput;
}

/*Perform back propogation*/
void NeuralNetwork::backPropogate(double* expectedOutputs, double* inputs)
{
	//Get the deltas of the output layer
	double* deltas = outputLayer->backPropogate(expectedOutputs);
	//Get deltas of each hidden layer
	for(int i = this->layers->getLength() - 1; i >= 0; i--)
	{
		
		if(i == this->layers->getLength() - 1)
		{
			deltas = (*this->layers)[i].backPropogate(deltas, (Layer*)outputLayer);
		}
		else
		{
			deltas = (*this->layers)[i].backPropogate(deltas, (Layer*)(&(*this->layers)[i+1]));
		}
	}

	//adjust each layer 
	outputLayer->adjust((&(*this->layers)[this->layers->getLength() - 1]));
	for(int i = this->layers->getLength() - 1; i>=1; i--)
	{
		(*this->layers)[i].adjust((&(*this->layers)[i-1]));
	}
	(*this->layers)[0].adjustWithInputs(inputs);
}	
#endif
