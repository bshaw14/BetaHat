#include<iostream>
#include"LinkedList.h"
using namespace std;

int main()
{
	LinkedList<int> ll;
	for(int i = 0; i < 10; i++)
	{
		ll.add(&i);
	}
	cout<<"Values added"<<endl;
	ll.reverse();
	for(int i = 0; i < ll.getLength(); i++)
	{
		cout<<ll[i]<<endl;
	}
}
