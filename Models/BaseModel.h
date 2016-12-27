/*Author: Austin Graham*/
#ifndef BASE_H
#define BASE_H
/*Defines the very base Model class, which will contain an ID for use
in web API*/
class Model
{
public:
	//Do nothing constructor
	Model(long id);
	//Do nothing destructor
	virtual ~Model() {}
	//Get this model's id
	int getID();
protected:
	//Id of the model, will be generated in web
	long id;
};

//Meh constructor
Model::Model(long id)
{
	this->id = id;
}

//Return the id of this model
int Model::getID()
{
	return this->id;
}

/*Defines a Supervised learning model, inheriting from a base model*/
class SupervisedModel : public Model
{
public:
	//Construct this model
	SupervisedModel(long id);
	//Destruct this model
	virtual ~SupervisedModel() {}
	//Train the model: to be defined in concrete classes
	virtual void Train(int epochs) = 0;
	//Classify inputs on this model: to be defined in concrete classes
	virtual double* Classify(double* inputs) = 0;
	//Get the success rate of this model on validation set
	double getSuccessRate();
protected:
	//Success rate of model on validation set
	double successRate;
};

/*Construct this model with default success of 0*/
SupervisedModel::SupervisedModel(long id) : Model(id)
{
	this->successRate = 0;
}

/*Get the success rate of the model*/
double SupervisedModel::getSuccessRate()
{
	return this->successRate;
}

/*Defines an unsupervised learning model*/
class UnsupervisedModel : public Model
{
public:
	//Construct this model using parent constructor
	UnsupervisedModel(long id) : Model(id) {}
	//Destroy this model
	virtual ~UnsupervisedModel() {}
	//Train this model: to be defined in concrete classes
	virtual void Train() = 0;
	//Classify input on this model: to be defined in concrete classes
	virtual double* Classify(double* inputs) = 0;
};
#endif
