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
protected:
	Matrix<double>* inputData;
	Matrix<double>* expectedData;
	int split;
	int nextAvailable;
	double ratio;
	LinkedList<int>* trainingSet;
	LinkedList<int>* testSet;
	Random* r;
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
	this->split = split;
}

void TrainingSet::splitData()
{
	int testSetSize = trainingSet->getLength() * ratio;
	for(int i = 0; i < testSetSize; i++)
	{
		int newRow = r->random_num(0, inputData->getRows());
		while(testSet->find(newRow) != -1)
		{
			newRow = r->random_num(0,inputData->getRows());
		}
		int toAdd = trainingSet->removeAt(newRow);
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
