#include<iostream>
#include"Structures/Stack.h"
using namespace std;

int main()
{
	Stack<int>* s = new Stack<int>();
	for(int i = 0; i < 10; i++)
	{
		s->push(&i);
	}
	cout<<"Top of list: "<<s->peek()<<endl;
	int maxSize = s->getSize();
	for(int i = 0; i < maxSize; i++)
	{
		cout<<s->pop()<<endl;
	}
	delete s;
	return 0;
}
