#pragma once
#include "bstNode.h"
#include <cmath>
#include <iomanip>
#include <queue>
#define COUNT 10

template<typename T>
class bst {
private:
	int numOperAdd;
	int numOperDel;
public:
	bstNode<T>* root;
	//default constructor
	bst();
	//destructor
	~bst();
	//constructor with data initialized
	bst(T data);
	//insert bstNode<T>* into bst with a type T data key
	bstNode<T>* insert(bstNode<T>* node, T key);
	//delete a bstNode<T>* from the bst with a type T data key
	bstNode<T>* deleteNode(bstNode<T>* node, T key);
	//search through bst for node with T data and return true or false
	bool search(T data);
	//print out the bst tree with spacing
	void printTreeSpace(bstNode<T>*, int space);
	//print out the tree in breadth first traversal into ofstream of choice
	void printBFS(bstNode<T>* root, ofstream& out);
	void printEfficiency();
};

template<typename T>
inline bst<T>::bst()
{
	root = nullptr;
	numOperAdd = 0;
	numOperDel = 0;
}

template<typename T>
inline bst<T>::bst(T data)
{
	root = new bstNode<T>(data);
	numOperAdd = 0;
	numOperDel = 0;
}

template<typename T>
inline bst<T>::~bst()
{
}

template<typename T>
inline bstNode<T>* bst<T>::insert(bstNode<T>* node, T key)
{
	numOperAdd++;
	if (node == NULL) {
		numOperAdd++;
		bstNode<T>* n = new bstNode<T>(key);
		return n;
	}
	numOperAdd++;
	if (key->getUsrName() < node->getData()->getUsrName()) {
		numOperAdd++;
		node->setLeft(insert(node->getLeft(), key));
	}
	else
	{
		numOperAdd++;
		node->setRight(insert(node->getRight(), key));
	}
	return node;

}


template<typename T>
inline bstNode<T>*  bst<T>::deleteNode(bstNode<T>* node, T key)
{
	numOperDel++;
	if (node == NULL) {
		return node;
	}
	numOperDel++;
	if (key->getUsrName() < node->getData()->getUsrName()) {

		node->setLeft(deleteNode(node->getLeft(), key));
		return node;
	}
	numOperDel++;
	if (key->getUsrName() > node->getData()->getUsrName()) {

		node->setRight(deleteNode(node->getRight(), key));
		return node;
	}
	// node to be deleted 
	else
	{
		numOperDel++;
		// node with only one child or no child 
		if (node->getLeft() == NULL)
		{
			numOperDel++;
			bstNode<T> *temp = node->getRight();
			delete node;
			return temp;
		}
		numOperDel++;
		if (node->getRight() == NULL)
		{
			numOperDel++;
			bstNode<T> *temp = node->getLeft();
			delete node;
			return temp;
		}

		// node with two children: inorder successor
		bstNode<T> *currentNode = node->getRight();
		bstNode<T> *tmp = node->getRight();
		numOperDel++;
		while (currentNode->getLeft() != NULL) {
			numOperDel++;
			tmp = currentNode;
			numOperDel++;
			currentNode = currentNode->getLeft();
			numOperDel++;
		}
		numOperDel++;
		tmp->setLeft(currentNode->getRight());
		// Copy the inorder successor
		numOperDel++;
		node->setRoot(currentNode->getData());
		numOperDel++;
		delete currentNode;
		return node;
	}
}

template<typename T>
inline bool bst<T>::search(T data)
{
	bstNode<T> *currentNode = root;

	while (currentNode != NULL) {
		if (currentNode->getData()->getUsrName() > data->getUsrName()) {
			currentNode = currentNode->getLeft();
		}  //else go to right tree
		else if (currentNode->getData()->getUsrName() < data->getUsrName()) {
			currentNode = currentNode->getRight();
		}
		else {
			return true;
		}
	}
	return false;
}

template<typename T>
inline void bst<T>::printTreeSpace(bstNode<T>* node, int space)
{
	if (node == NULL)
		return;
	space += COUNT;
	printTreeSpace(node->getRight(), space);
	printf("\n");
	for (int i = COUNT; i < space; i++)
		printf(" ");
	cout << ((node->getData())->getUsrName()) << "\n";
	printTreeSpace(node->getLeft(), space);
}



template<typename T>
inline void bst<T>::printBFS(bstNode<T>* root, ofstream& out) {
	bstNode<T>* curr = root;
	queue<bstNode<T>*> q;
	while (curr) {
		out << curr->getData()->getUsrName() << endl;
		out << curr->getData()->getPsw() << endl;
		out << curr->getData()->getBirthday() << endl;
		out << curr->getData()->getEmail() << endl;
		if (curr->getLeft()) {
			q.push(curr->getLeft());
		}
		if (curr->getRight()) {
			q.push(curr->getRight());
		}
		if (!q.empty()) {
			curr = q.front();
			q.pop();
		}
		else {
			curr = NULL;
		}

	}
}


template<typename T>
inline void bst<T>::printEfficiency()
{
	cout << "Number of Operation of Add:" << numOperAdd << endl;
	cout << "Number of Operation of Delete: " << numOperDel << endl;

}
