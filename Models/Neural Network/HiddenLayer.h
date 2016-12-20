/*Author: Austin Graham*/
#ifndef HIDDENLAYER_H
#define HIDDENLAYER_H
#include"Layer.h"
#include<iostream>
using namespace std;
class HiddenLayer : public Layer
{
public:
	HiddenLayer(int size, int prevLayerSize) : Layer(size, prevLayerSize){}
	~HiddenLayer(){}
	double* backPropogate(double* deltas);	
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

double* HiddenLayer::backPropogate(double* deltas)
{
	return NULL;
}
#endif
