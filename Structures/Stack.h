#include"LinkedList.h"

/*Defines the Stack data structure*/
template<class DT>
class Stack
{
public:
	//Construct an empty stack
	Stack();
	//Deconstruct a stack
	~Stack();
	//Push a value onto the stack
	void push(DT* newVal);
	//Peek the top of the stack
	DT peek();
	//Remove from the top of the stack
	DT pop();
	//Get the size of the stack
	int getSize();
private:
	//LinkedList containing the data in the stack
	LinkedList<DT>* data;
};

/*Create the stack*/
template<class DT>
Stack<DT>::Stack()
{
	//Initialize the stack content list
	this->data = new LinkedList<DT>();
}

/*Deconstruct the stack*/
template<class DT>
Stack<DT>::~Stack()
{
	//Delete the stack contents
	delete this->data;
}

/*Push data onto the top of the stack*/
template<class DT>
void Stack<DT>::push(DT* newVal)
{
	this->data->addAt(newVal, 0);
}

/*Return the data on the top of the stack*/
template<class DT>
DT Stack<DT>::peek()
{
	return (*this->data)[0];
}

/*Remove the data off the top of the stack*/
template<class DT>
DT Stack<DT>::pop()
{
	return this->data->remove();
}

/*Get the size of the stack*/
template<class DT>
int Stack<DT>::getSize()
{
	return this->data->getLength();
}
