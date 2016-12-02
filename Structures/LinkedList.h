/*Author: Austin Graham*/
#include"../memory.h"
using namespace std;

/*Data structure storing items of a certain type
into a list*/
template<class DT>
class LinkedList
{
public:
	//Constructor
	LinkedList();
	//Destructor
	~LinkedList();
	//Add at the end of the list
	void add(DT* newVal);
	//Add at a certain index of the list
	void addAt(DT* newVal, int index);
	//Remove from the front of the list
	DT remove();
	//Remove at a particular index of the list
	DT removeAt(int index);
	//Get an element in the list
	DT& operator[](int index);
	//Get the length of the list
	int getLength();
	//Reverse the list
	void reverse();
private:
	//Structure of each node in the list
	struct LinkedListNode
	{
		LinkedListNode* next;
		DT* data;
	};
	//Length of the list
	int length;
	//Head of the list
	LinkedListNode* head;
};

/*Construct an empty list*/
template<class DT>
LinkedList<DT>::LinkedList()
{
	this->length = 0;
	this->head = NULL;
}

/*Deconstruct the list*/
template<class DT>
LinkedList<DT>::~LinkedList()
{
	//Iterate through the list deleting all nodes
	LinkedListNode* next;
	while(this->head)
	{
		next = this->head->next;
		delete this->head;
		this->head = next;
	}
}

/*Add a new node to the end of the list*/
template<class DT>
void LinkedList<DT>::add(DT* newVal)
{
	//Construct a new node
	LinkedListNode* newNode = new LinkedListNode;
	newNode->next = NULL;
	newNode->data = new DT[1];
	mem_cpy(newVal, newNode->data, sizeof(DT));

	//increment the length
	this->length++;

	//If the list is empty, assign the head
	if(this->head == NULL)
	{
		this->head = newNode;
		return;
	}

	//Otherwise, iterate to the end and add
	LinkedListNode* current = this->head;
	while(current->next != NULL)
	{
		current = current->next;
	}
	current->next = newNode;
}

/*Add a node anywhere in the list*/
template<class DT>
void LinkedList<DT>::addAt(DT* newVal, int index)
{
	//Create the new node
	LinkedListNode* newNode = new LinkedListNode;
	newNode->next = NULL;
	newNode->data = new DT[1];
	mem_cpy(newVal, newNode->data, sizeof(DT));

	//Increment the length
	this->length++;

	//Add at front if index is zero
	if(index == 0)
	{
		newNode->next = this->head;
		this->head = newNode;
		return;
	}

	//Iterate to the desired index
	LinkedListNode* current = this->head;
	while(current != NULL && index > 1)
	{
		current = current->next;
		index--;
	}

	//Insert the node
	newNode->next = current->next;
	current->next = newNode;
}

/*Remove from the end of the list*/
template<class DT>
DT LinkedList<DT>::remove()
{
	//Save the value to return
	DT toReturn = (*this)[0];
	LinkedListNode* next = this->head->next;

	//Delete the node
	delete this->head;
	
	//Reassign the next node
	this->head = next;

	//Decrement length
	this->length--;

	//Return teh value
	return toReturn;
}

/*Remove an element anywhere in the list*/
template<class DT>
DT LinkedList<DT>::removeAt(int index)
{
	//If the first element, just remove
	if(index == 0)
	{
		return this->remove();
	}

	//Otherwise save the value to return
	DT toReturn = (*this)[index];

	//Go to the index
	LinkedListNode* current = this->head;
	while(current != NULL && index > 1)
	{
		current = current->next;
		index--;
	}

	//Remove the element at that index
	LinkedListNode* toDelete = current->next;
	current->next = current->next->next;
	delete toDelete;
	this->length--;
	return toReturn;
}

/*Get a particular element in the list*/
template<class DT>
DT& LinkedList<DT>::operator[](int index)
{
	//Go the give index
	int count = 0;
	LinkedListNode* current = this->head;
	
	while(current != NULL && count < index)
	{
		current = current->next;
		count++;
	}
	
	//Return that nodes value
	return (*current->data);
}

/*Return the length of the list*/
template<class DT>
int LinkedList<DT>::getLength()
{
	return this->length;
}

/*Reverse the list*/
template<class DT>
void LinkedList<DT>::reverse()
{
	//Initialize temp pointers
	LinkedListNode* current = this->head;
	LinkedListNode* next = NULL;
	LinkedListNode* prev = NULL;

	//Reverse all linkages
	while(current!=NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}

	//Set head to the last node
	this->head = prev;	
}
