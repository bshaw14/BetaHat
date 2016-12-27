/*Author: Austin Graham*/
#ifndef RANDOM_H
#define RANDOM_H
#include<ctime>
#include<cstdlib>

/*Generates random numbers*/
class Random
{
public:
	Random();
	~Random();
	//Get a random number between a min and max value
	double random_num(double min, double max);
};

Random::Random()
{
	//Seed the random
	srand(time(NULL));
}

Random::~Random() {}

/*Get the random number*/
double Random::random_num(double min, double max)
{
	return ((double)rand() / RAND_MAX) * (max - min) + min;
}
#endif
