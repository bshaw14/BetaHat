/*Author: Austin Graham*/
#ifndef OUTPUTLAYER_H
#define OUTPUTLAYER_H
#include"Layer.h"
#include<iostream>
using namespace std;
class OutputLayer : public Layer
{
public:
	OutputLayer(int size, int prevLayerSize) : Layer(size, prevLayerSize){}
	~OutputLayer(){}
	double* backPropogate(double* expectedOutputs);
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

double* OutputLayer::backPropogate(double* expectedOutputs)
{
	int deltaSize = this->size * this->inputSize;
	double* deltas = new double[deltaSize];
	for(int i = 0; i < this->size; i++)
	{
		double lastActivation = (*this->neurons)[i].getLastActivation();
		savedDeltas[i] = (lastActivation - expectedOutputs[i])*(1 - lastActivation)*lastActivation;
	}

	for(int i = 0; i < this->size; i++)
	{
		for(int j = 0; j< this->inputSize; j++)
		{
			deltas[i*j + j] = savedDeltas[i] * (*this->neurons)[i].getWeights()[j];		
		}
	}
	return deltas;
}
#endif
