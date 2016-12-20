/*Author: Austin Graham*/
#include<iostream>
#include"Models/Neural Network/NeuralNetwork.h"
#include"random.h"
using namespace std;

int main()
{
	int layers[] = {2,3,1};
	NeuralNetwork* nn = new NeuralNetwork(layers, 3);
	double inputs[] = {3.0, 4.0};
	double* outputs = nn->feedForward(inputs);
	cout<<"Outputs: "<<endl;
	cout<<outputs[0]<<endl;
	cout<<(*nn)<<endl;
	double expected[] = {1};
	nn->backPropogate(expected);
	delete nn;
	return 0;
}
