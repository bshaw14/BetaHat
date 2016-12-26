/*Author: Austin Graham*/
#ifndef OUTPUTLAYER_H
#define OUTPUTLAYER_H
#include"Layer.h"
#include<iostream>
using namespace std;

/*Encapsulates an Output Layer of an ANN*/
class OutputLayer : public Layer
{
public:
	//Construct the layer
	OutputLayer(int size, int prevLayerSize) : Layer(size, prevLayerSize){}
	//Destroy the layer
	~OutputLayer(){}
	//Perform back propogation of on an observation
	double* backPropogate(double* expectedOutputs);
	//Show layer data
	friend ostream& operator<<(ostream& os, const OutputLayer& o)
	{
		os<<"OUTPUT LAYER:"<<endl;
		os<<"Size: "<<o.size<<endl;
		os<<"NEURONS:"<<endl;
		for(int i = 0; i < o.size; i++)
		{
			os<<(*o.neurons)[i]<<endl;
		}
		return os;
	}
};

/*Perform back propogation*/
double* OutputLayer::backPropogate(double* expectedOutputs)
{
	//For each Neuron, use the expected values to calculate how much each Neuron screwed up
	for(int i = 0; i < this->size; i++)
	{
		double lastActivation = (*this->neurons)[i].getLastActivation();
		savedDeltas[i] = (lastActivation - expectedOutputs[i])*(1 - lastActivation)*lastActivation;
		this->biases[i] -= learningConstant * savedDeltas[i];
	}
	return savedDeltas;
}
#endif
