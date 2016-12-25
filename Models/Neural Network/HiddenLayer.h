/*Author: Austin Graham*/
#ifndef HIDDENLAYER_H
#define HIDDENLAYER_H
#include"Layer.h"
#include"Neuron.h"
#include<iostream>
using namespace std;
class HiddenLayer : public Layer
{
public:
	HiddenLayer(int size, int prevLayerSize) : Layer(size, prevLayerSize){}
	~HiddenLayer(){}
	double* backPropogate(double* deltas, Layer* prevLayer);	
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

double* HiddenLayer::backPropogate(double* deltas, Layer* prevLayer)
{
	for(int i = 0; i < this->size; i++)
	{
		double sum = 0;
		
		for(int k = 0; k < prevLayer->getSize(); k++)
		{
			sum += (*prevLayer)[k].getWeights()[i] * deltas[k];
		}
		
		
		savedDeltas[i] = sum*(1-(*this->neurons)[i].getLastActivation())*(*this->neurons)[i].getLastActivation();
		this->biases[i] -= savedDeltas[i] * learningConstant;
	}
	return savedDeltas;
}
#endif
