#pragma once
#include <iostream>
using namespace std;

template<typename K, typename V>

class hashNode {
protected:
	K key;
	V value;
	hashNode<K, V>* next;
public:

	hashNode(K key, V value);
	K getKey();
	V getValue();
	hashNode<K, V>* getNext();
	void setKey(K k);
	void setValue(V v);
	void setNext(hashNode<K, V>* h);



};

//hashnode default constructor
//taking in one key argument and one value argument
template<typename K, typename V>
hashNode<K, V>::hashNode(K k, V v) {
	key = k;
	value = v;
}

//return the key of the hashnode
template<typename K, typename V>
K hashNode<K, V>::getKey() {
	return key;
}

//return the value of the hashnode
template<typename K, typename V>
V hashNode<K, V>::getValue() {
	return value;
}

//return the next pointer of the hashnode
template<typename K, typename V>
hashNode<K, V>* hashNode<K, V>::getNext() {
	return next;
}

//set the key field inside hashnode equal to the parameter
template<typename K, typename V>
void hashNode<K, V>::setKey(K keys) {
	key = keys;
}

//set the value field inside hashnode equal to the parameter
template<typename K, typename V>
void hashNode<K, V>::setValue(V values) {
	value = values;
}

//set the next field inside hashnode equal to the parameter
template<typename K, typename V>
void hashNode<K, V>::setNext(hashNode<K, V>* h) {
	next = h;
}
