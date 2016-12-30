#ifndef TRAININGSET_H
#define TRAININGSET_H
#include"Matrix.h"
#include"LinkedList.h"
#include"../random.h"
#include<iostream>
using namespace std;
class TrainingSet
{
public:
	TrainingSet(int featureLength, int outputLength, int numberOfObservations);
	virtual ~TrainingSet();
	void setRatio(double split);
	void splitData();
	void addObservation(double* input, double* output);
	void randomize();
	Matrix<double>* getTrainingSetInput();
	Matrix<double>* getTrainingSetOutput();
	Matrix<double>* getTestSetInput();
	Matrix<double>* getTestSetOutput();
protected:
	Matrix<double>* inputData;
	Matrix<double>* expectedData;
	int nextAvailable;
	double ratio;
	LinkedList<int>* trainingSet;
	LinkedList<int>* testSet;
	Random* r;	
	int featureLength;
	int outputLength;
	void reset();
};

TrainingSet::TrainingSet(int featureLength, int outputLength, int numberOfObservations)
{
	inputData = new Matrix<double>(numberOfObservations, featureLength, -1);
	expectedData = new Matrix<double>(numberOfObservations, outputLength, -1);
	ratio = .3;
	r = new Random();
	trainingSet = new LinkedList<int>();
	testSet = new LinkedList<int>();
	for(int i = 0; i< numberOfObservations; i++)
	{
		trainingSet->add(&i);
	}
	nextAvailable = 0;
	this->featureLength = featureLength;
	this->outputLength = outputLength;
}

TrainingSet::~TrainingSet()
{
	delete inputData;
	delete expectedData;
	delete trainingSet;
	delete testSet;
}

void TrainingSet::setRatio(double split)
{
	if(split > 1 || split < 0) return;
	this->ratio = split;
}

void TrainingSet::splitData()
{
	int testSetSize = trainingSet->getLength() * ratio;
	for(int i = 0; i < testSetSize; i++)
	{
		int newRow = r->random_num(0, inputData->getRows() - 1);
		while(testSet->find(newRow) != -1)
		{
			newRow = r->random_num(0,inputData->getRows() - 1);
		}
		int toAdd = trainingSet->removeAt(trainingSet->find(newRow));
		testSet->add(&toAdd);
	}
}

void TrainingSet::addObservation(double* input, double* output)
{
	for(int i = 0; i < inputData->getColumns(); i++)
	{
		inputData->set(nextAvailable, i, input[i]);
	}
	
	for(int i = 0; i < expectedData->getColumns(); i++)
	{
		expectedData->set(nextAvailable, i, output[i]);
	}

	nextAvailable++;
}

void TrainingSet::randomize()
{
	reset();
	LinkedList<int>* randomList = new LinkedList<int>();
	for(int i = 0; i < inputData->getRows(); i++)
	{
		int newRow = r->random_num(0, trainingSet->getLength() - 1);
		int toAdd = trainingSet->removeAt(newRow);
		randomList->add(&toAdd);
	}
	delete trainingSet;
	trainingSet = randomList;
}

Matrix<double>* TrainingSet::getTrainingSetInput()
{
	Matrix<double>* returnSet = new Matrix<double>(trainingSet->getLength(), featureLength, -1);
	for(int i = 0; i < trainingSet->getLength(); i++)
	{
		for(int j = 0; j < featureLength; j++)
		{
			returnSet->set(i,j,inputData->get((*trainingSet)[i],j));
		}
	}
	return returnSet;
}

Matrix<double>* TrainingSet::getTrainingSetOutput()
{
	Matrix<double>* returnSet = new Matrix<double>(trainingSet->getLength(), outputLength, -1);
	for(int i = 0; i < trainingSet->getLength(); i++)
	{
		for(int j = 0; j < outputLength; j++)
		{
			returnSet->set(i,j,expectedData->get((*trainingSet)[i],j));
		}
	}
	return returnSet;
}

Matrix<double>* TrainingSet::getTestSetInput()
{
	Matrix<double>* returnSet = new Matrix<double>(testSet->getLength(), featureLength, -1);
	for(int i = 0; i < testSet->getLength(); i++)
	{
		for(int j = 0; j < featureLength; j++)
		{
			returnSet->set(i,j,inputData->get((*testSet)[i],j));
		}
	}
	return returnSet;
}

Matrix<double>* TrainingSet::getTestSetOutput()
{
	Matrix<double>* returnSet = new Matrix<double>(testSet->getLength(), outputLength, -1);
	for(int i = 0; i < testSet->getLength(); i++)
	{
		for(int j = 0; j < outputLength; j++)
		{
			returnSet->set(i,j,expectedData->get((*testSet)[i],j));
		}
	}
	return returnSet;
}

void TrainingSet::reset()
{
	delete testSet;
	testSet = new LinkedList<int>();
	delete trainingSet;
	trainingSet = new LinkedList<int>();
	for(int i = 0; i < inputData->getRows(); i++)
	{
		trainingSet->add(&i);
	}
	this->nextAvailable = 0;
}
#endif
