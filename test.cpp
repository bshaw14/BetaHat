#include<iostream>
#include"Structures/TrainingSet.h"
using namespace std;

int main()
{
	TrainingSet* t = new TrainingSet(76, 110, 10);
	t->splitData();
	delete t;
	return 0;
}
