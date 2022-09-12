#pragma once
#include <iostream>
using namespace std;

template<typename T>
class node
{

private:
	T data;
	node<T>* next;

public:
	~node();
	node();
	T getData();
	void setData(T d);
	void setNext(node<T>* pnext);
	node<T>* getNext();
	node(T d);

};

//default constructor
template<typename T>
node<T>::node()
{

}

//return the data inside the node
template<typename T>
T node<T>::getData()
{
	return data;
}

//set data equal to the function parameter
template<typename T>
void node<T>::setData(T d)
{
	data = d;
}

//set next pointer equal to the function parameter
template<typename T>
void node<T>::setNext(node<T>* pnext)
{
	next = pnext;
}

//return the next pointer
template<typename T>
node<T>* node<T>::getNext()
{
	return next;
}

//constructor that takes in a data argument
//assign the data filed with the value of the parameter
template<typename T>
node<T>::node(T d)
{
	data = d;
	next = nullptr;
}

//default destructor 
template<typename T>
node<T>::~node() {}

