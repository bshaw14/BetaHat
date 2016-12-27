/*Author: Austin Graham*/
#include<iostream>
#include"Models/Neural Network/NeuralNetwork.h"
#include"random.h"
using namespace std;

int main()
{
	cout<<"Building training data..."<<endl;
	Random r;
	double** observations = new double*[100];
	double** expected = new double*[100];
	for(int i = 0; i< 100; i++)
	{
		observations[i] = new double[2];
		observations[i][0] = (r.random_num(0,1) >= .5) ? 1: 0;
		observations[i][1] = (r.random_num(0,1) >= .5) ? 1: 0;
		expected[i] = new double[1];
		expected[i][0] = (int)observations[i][0] ^ (int)observations[i][1];
	}	

	cout<<"Training network..."<<endl;
	int layers[] = {2,3,1};
	NeuralNetwork* nn = new NeuralNetwork(layers, 3, 15);
	for(int k = 0; k < 500; k++)
	{
		for(int i = 0; i < 100; i++)
		{
			double* results = nn->feedForward(observations[i]);
			double out = (results[0] >= .5) ? 1 : 0;
			//cout<<"Cost: "<<.5*(expected[i][0] - results[0])*(expected[i][0] - results[0])<<endl;
			//cout<<"********\nInput: "<<observations[i][0]<<", "<<observations[i][1]<<endl;
			//cout<<"Results: "<<out<<endl<<"********"<<endl;
			nn->backPropogate(expected[i], observations[i]);
		}
	}
	cout<<"Trained."<<endl;
	cout<<"Network ID: "<<nn->getID()<<endl;

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
	for(int i = 0; i < 100; i++)
	{
		delete [] observations[i];
	}
	delete [] observations;
	delete [] expected;
	delete nn;
	cout<<"Done."<<endl;

	return 0;
}
