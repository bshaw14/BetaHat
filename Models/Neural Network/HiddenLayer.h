/*Author: Austin Graham*/
#ifndef HIDDENLAYER_H
#define HIDDENLAYER_H
#include"Layer.h"
#include"Neuron.h"
#include<iostream>
using namespace std;

/*Encapsulates a hidden layer of a neural network, taking attributes
from a Layer object*/
class HiddenLayer : public Layer
{
public:
	//Construct the HiddenLayer using Layer constructor
	HiddenLayer(int size, int prevLayerSize) : Layer(size, prevLayerSize){}
	//Defaults to Layer destructor
	~HiddenLayer(){}
	//Perform back propogation on this HiddenLayer
	double* backPropogate(double* deltas, Layer* prevLayer);
	//Output the layer	
	friend ostream& operator<<(ostream& os, const HiddenLayer& h)
	{
		os<<"HIDDEN LAYER:"<<endl;
		os<<"Size: "<<h.size<<endl;
		os<<"NEURONS:"<<endl;
		for(int i = 0; i < h.size; i++)
		{
			os<<(*h.neurons)[i]<<endl;
		}
		return os;
	}
};

/*Perform back propogation on this HiddenLayer*/
double* HiddenLayer::backPropogate(double* deltas, Layer* prevLayer)
{
	//For every Neuron in this layer
	for(int i = 0; i < this->size; i++)
	{
		//Sum all backwards deltas and multiply by the connecting weight
		//to get the amount this neuron contributed to the total error
		double sum = 0;
		
		for(int k = 0; k < prevLayer->getSize(); k++)
		{
			sum += (*prevLayer)[k].getWeights()[i] * deltas[k];
		}
		
		//Multiply this sum by the derivative of the sigmoid, save in object
		savedDeltas[i] = sum*(1-(*this->neurons)[i].getLastActivation())*(*this->neurons)[i].getLastActivation();
		//Use this value to adjust the bias
		this->biases[i] -= savedDeltas[i] * learningConstant;
	}
	return savedDeltas;
}
#endif
