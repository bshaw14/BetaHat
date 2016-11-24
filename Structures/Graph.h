#include<iostream>
#include<vector>
#include"Matrix.h"
using namespace std;

class Graph
{
public:
	Graph();
	~Graph();
	void addVertex(int label);
	void addEdge(int vertex1, int vertex2, double weight);
	double getEdge(int vertex1, int vertex2);
	void setEdge(int vertex1, int vertex2, double newVal);
	int* getVertexAdjacent(int label);
	double* getVertexWeights(int label);
	int getVertexCount();
	const static int END;
	const static double ERROR;
private:
	Matrix<double>* adjacency;
};

const int Graph::END = -1;
const double Graph::ERROR = -99.9999;

Graph::Graph()
{
	this->adjacency = new Matrix<double>(0,0,ERROR);
}

Graph::~Graph()
{
	delete adjacency;
}

void Graph::addVertex(int label)
{
	adjacency->extend(1,1);
}

void Graph::addEdge(int vertex1, int vertex2, double weight)
{
	adjacency->set(vertex1, vertex2, weight);
	adjacency->set(vertex2, vertex1, weight);
}

double Graph::getEdge(int vertex1, int vertex2)
{
	return adjacency->get(vertex1, vertex2);	
}

void Graph::setEdge(int vertex1, int vertex2, double newVal)
{
	adjacency->set(vertex1, vertex2, newVal);
}

int* Graph::getVertexAdjacent(int label)
{
	vector<int>* adjacents = new vector<int>();
	for(int i = 0; i < adjacency->getColumns(); i++)
	{
		if(adjacency->get(label, i) != ERROR)
		{
			adjacents->push_back(i);
		}
	}
	int* asArray = new int[adjacents->size() + 1];
	for(int i = 0; i<adjacents->size();i++)
	{
		asArray[i] = adjacents->at(i);
	}
	asArray[adjacents->size()] = END;
	delete adjacents;
	return asArray;
}

double* Graph::getVertexWeights(int label)
{
	vector<double>* adjacents = new vector<double>();

	for(int i = 0; i < adjacency->getColumns(); i++)
	{
		if(adjacency->get(label, i) != ERROR)
		{
			adjacents->push_back(adjacency->get(label, i));
		}
	}
	double* asArray = new double[adjacents->size() + 1];
	for(int i = 0; i<adjacents->size();i++)
	{
		asArray[i] = adjacents->at(i);
	}
	asArray[adjacents->size()] = ERROR;
	delete adjacents;
	return asArray;
}


int Graph::getVertexCount()
{
	return adjacency->getRows();
}
