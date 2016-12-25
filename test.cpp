/*Author: Austin Graham*/
#include<iostream>
#include"Models/Neural Network/NeuralNetwork.h"
#include"random.h"
using namespace std;

int main()
{
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


	int layers[] = {2,3,1};
	NeuralNetwork* nn = new NeuralNetwork(layers, 3);
	for(int k = 0; k < 500; k++)
	{
		for(int i = 0; i < 100; i++)
		{
			double* results = nn->feedForward(observations[i]);
			double out = (results[0] >= .5) ? 1 : 0;
			//cout<<"Cost: "<<.5*(expected[i][0] - results[0])*(expected[i][0] - results[0])<<endl;
			cout<<"********\nInput: "<<observations[i][0]<<", "<<observations[i][1]<<endl;
			cout<<"Results: "<<out<<endl<<"********"<<endl;
			nn->backPropogate(expected[i], observations[i]);
		}
	}

	for(int i = 0; i < 100; i++)
	{
		delete [] observations[i];
	}
	delete [] observations;
	delete [] expected;
	delete nn;

	return 0;
}
