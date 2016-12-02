#include"Neuron.h"
#include"../Structures/LinkedList.h"

class Layer
{
public:
	Layer(int size);
	~Layer();
	int getSize();
	double* feed(double* activations);
	double* backPropogate(double* deltas);
private:
	LinkedList<Neuron> neurons;
	int size;
	double bias;
}

Layer::Layer(int size, int prevLayerSize)
{
	this->neurons = new LinkedList<Neuron>();
	for(int i = 0; i < this->size; i++)
	{
		neurons->add(new Neuron(prevLayerSize));
	}
	this->size = size;
	this->bias = 1;
}

Layer::~Layer()
{
	delete neurons;
}

int Layer::getSize()
{
	return this->size;
}
