/*Author: Austin Graham*/
#include<iostream>
#include"../../Models/Neural Network/NeuralNetwork.h"
#include"../../random.h"
#include"../../Structures/TrainingSet.h"
using namespace std;

void normalize(double* vals, int count)
{
	for(int i = 0; i < count; i++)
	{
		vals[i] = (vals[i] >= .5) ? 1 : 0;
	}
}

int main()
{
	cout<<"Building training data..."<<endl;
	Random r;
	TrainingSet* tr = new TrainingSet(2,1,100);
	for(int i = 0; i< 100; i++)
	{
		double input[] = {(r.random_num(0,1) >= .5) ? 1: 0,(r.random_num(0,1) >= .5) ? 1: 0};
		double output[] = {(int)input[0] ^ (int)input[1]};
		tr->addObservation(input, output);
	}	

	cout<<"Training network..."<<endl;
	int layers[] = {2,6,3,1};
	NeuralNetwork* nn = new NeuralNetwork(layers, 4, 15);
	nn->Train(100, tr, normalize);
	cout<<"Trained."<<endl;
	cout<<"Network ID: "<<nn->getID()<<endl;
	cout<<"Network Success Rate: "<<nn->getSuccessRate()*100<<"%"<<endl;

	double x = 0;
	double y = 0;
	
	while(true)
	{
		cout<<"Enter two values to be fed:"<<endl;
		cout<<"X: ";
		cin>>x;
		if(x != 1 && x != 0)
		{
			break;
		}
		cout<<"Y: ";
		cin>>y;
		double inputs[] = {x,y};
		cout<<"X ^ Y: "<<((nn->Classify(inputs)[0] >= .5) ? 1.0 : 0.0)<<endl;
	}

	cout<<"Cleaning up..."<<endl;
	delete nn;
	cout<<"Done."<<endl;

	return 0;
}
