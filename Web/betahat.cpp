#include<Python.h>
#include<boost/python.hpp>
#include<boost/python/module.hpp>
#include<boost/python/def.hpp>
#include"../Models/Neural Network/NeuralNetwork.h"
#include"../Structures/TrainingSet.h"
#include<iostream>
using namespace std;
using namespace boost::python;

void normalize(double* output, int count)
{
	for(int i = 0; i < count; i++)
	{
		output[i] = (output[i] >= .5) ? 1 : 0;
	}
}

class PyTrainingSet
{
public:
	PyTrainingSet(int featureLength, int outputLength, int numberOfObservations)
	{
		set = new TrainingSet(featureLength, outputLength, numberOfObservations);
	}
	PyTrainingSet(const PyTrainingSet& old)
	{
		set = new TrainingSet(old.set);
	}
	~PyTrainingSet()
	{
		delete set;
	}
	void setRatio(double newRatio)
	{
		set->setRatio(newRatio);
	}
	void addObservation(list input, list output)
	{
		int inputSize = len(input);
		int outputSize = len(output);
		double* inputAsArray = new double[inputSize];
		double* outputAsArray = new double[outputSize];
		for(int i = 0; i < inputSize; i++)
		{
			inputAsArray[i] = extract<double>(input[i]);
		}
		for(int i = 0; i < outputSize; i++)
		{
			outputAsArray[i] = extract<double>(output[i]);
		}
		set->addObservation(inputAsArray, outputAsArray);
	}
	TrainingSet* set;
};

class PyNetwork
{
public:   
	PyNetwork(list layers, int layerCount, long id)
	{
		int size = len(layers);
		int* asArray = new int[size];
		for(int i = 0; i < size; i++)
		{
			asArray[i] = extract<int>(layers[i]);
		}
		nn = new NeuralNetwork(asArray, layerCount, id);
		outputSize = extract<double>(layers[layerCount - 1]);
	}
	~PyNetwork()
	{
		delete this->nn;
	}
	double getSuccessRate()
	{
		return nn->getSuccessRate();
	}
	void Train(int epochs, object tSet)
	{
		PyTrainingSet s = extract<PyTrainingSet>(tSet);
		PyTrainingSet* useSet = new PyTrainingSet(s);
		nn->Train(epochs, useSet->set, normalize);
		delete useSet;
	}
	list Classify(list inputs)
	{
		int inputSize = len(inputs);
		double* inputsAsArray = new double[inputSize];
		for(int i = 0; i < inputSize; i++)
		{
			inputsAsArray[i] = extract<double>(inputs[i]);
		}
		double* outputs = nn->Classify(inputsAsArray);
		list asList;
		for(int i = 0; i < outputSize; i++)
		{
			asList.append(outputs[i]);
		}
		return asList;
	}
protected:
	NeuralNetwork* nn;
	int outputSize;
};

BOOST_PYTHON_MODULE(betahat)
{
	class_<PyNetwork>("NeuralNetwork", init<list, int, long>())
		.def("Train", &PyNetwork::Train)
		.def("Classify", &PyNetwork::Classify)
		.def("getSuccessRate", &PyNetwork::getSuccessRate)
	;

	class_<PyTrainingSet>("TrainingSet", init<int, int, int>())
		.def("setRatio", &PyTrainingSet::setRatio)
		.def("addObservation", &PyTrainingSet::addObservation)
	;
}
