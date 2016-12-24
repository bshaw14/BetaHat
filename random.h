#ifndef RANDOM_H
#define RANDOM_H
#include<ctime>
#include<cstdlib>

class Random
{
public:
	Random();
	~Random();
	double random_num(double min, double max);
};

Random::Random()
{
	srand(10);
}

Random::~Random() {}

double Random::random_num(double min, double max)
{
	return ((double)rand() / RAND_MAX) * (max - min) + min;
}
#endif
