#pragma once
#include "hashNode.h"
#include <string>
#include <cmath>
//hashtable using chaining for collision resolution 
template<typename K, typename V>
class hashtable
{
private:
    hashNode<K, V>** bucketList;
    int numBuckets;
    int sizes;
    size_t hashCode(K key);
    int getBucketIndex(K key);
    int collision;
    
public:
    
    hashtable();
    int size();
    bool isEmpty();
    void remove(K key);
    void add(K key, V value);
    bool hasKey(K key);
    V get(K key);
    int getCollision();
    double getLoadFactor();
    void print();
};

//default hashtable constructor
template<typename K, typename V>
inline hashtable<K, V>::hashtable()
{
    bucketList = new hashNode<K, V>*[10];
    numBuckets = 10;
    sizes = 0;
    
    for (int i = 0; i < numBuckets; i++) {
        bucketList[i] = nullptr;
    }
}

//return the number of elements stored in hashtable
template<typename K, typename V>
int hashtable<K, V>::size()
{
    return sizes;
}

//return true if the hashtable is empty
template<typename K, typename V>
bool hashtable<K, V>::isEmpty()
{
    return size() == 0;
}

//return the hash value of the key
//the hash value is the sum of the every character's value times its index to the power of 31
template<typename K, typename V>
size_t hashtable<K, V>::hashCode(K key) {
	
		int result = 0;
		for (size_t i = 0; i < key.length(); ++i) {
			result += key[i] * pow(31, i);
		}
		return result;
	
}

//return the index of the key inside the bucket array
template<typename K, typename V>
int hashtable<K, V>::getBucketIndex(K key)
{
    size_t hashV = hashCode(key);
    int index = (int)(hashV % numBuckets);
    
    return index;
}

//remove the hashnode that has the specified key attibute
template<typename K, typename V>
void hashtable<K, V>::remove(K key)
{
    int bucketIndex = getBucketIndex(key);
    
    hashNode<K, V>* head = bucketList[bucketIndex];
    hashNode<K, V>* prev = nullptr;
    while (head) {
        if (head->getKey() == key) {
            break;
        }
        prev = head;
        head = head->getNext();
    }
    
    if (!head) {
        return;
    }
    
    sizes--;
    
    if (prev) {
        prev->setNext(head->getNext());
    }
    else {
        bucketList[bucketIndex] = head->getNext();
    }
    
}

//add a key and value pair inside the hashtable
template<typename K, typename V>
void hashtable<K, V>::add(K key, V value) {
   
    int bucketIndex = getBucketIndex(key);
    hashNode<K, V>* head = bucketList[bucketIndex];
    
    
    while (head != nullptr) {
        if (head->getKey() == key) {
            head->setValue(value);
            return;
        }
        head = head->getNext();
        collision++;
    }
    
    sizes++;
    head = bucketList[bucketIndex];

    hashNode<K, V>* newNode = new hashNode<K, V>(key, value);
    newNode->setNext(head);
    bucketList[bucketIndex] = newNode;
    
    if ((1.0*sizes) / numBuckets >= 0.7) {
        hashNode<K, V>** tmp = bucketList;
        bucketList = new hashNode<K, V>*[2 * numBuckets];
        numBuckets = 2 * numBuckets;
        sizes = 0;
        collision = 0;
        for (int i = 0; i < numBuckets; i++)
        {
            bucketList[i] = nullptr;
        }
        
        for (int i = 0; i < numBuckets / 2; i++) {
            hashNode<K, V>* headNode = tmp[i];
            while (headNode) {
                add(headNode->getKey(), headNode->getValue());
                headNode = headNode->getNext();
            }
        }
    }
}

//return true if the hashtable has the hashnode with the same key
template<typename K, typename V>
bool hashtable<K, V>::hasKey(K key)
{
    int bucketIndex = getBucketIndex(key);
    hashNode<K, V>* head = bucketList[bucketIndex];
    
    while (head) {
        if (head->getKey() == key) {
            return true;
        }
        head = head->getNext();
    }
    return false;
}

//return the value of the hashnode that has the same key
template<typename K, typename V>
V hashtable<K, V>::get(K key) {
    int bucketIndex = getBucketIndex(key);
    
    hashNode<K, V>* head = bucketList[bucketIndex];
    
    while (head) {
        if (head->getKey() == key) {
            return head->getValue();
        }
        head = head->getNext();
    }
    
    try {
        if (!head) {
            throw "cannot find the key";
        }
        
    }
    catch (const char*  err) {
        cout << err << endl;
    }
    return head->getValue();
}

//return the number of collision happened when adding hashnode into the hashtable
template<typename K, typename V>
int hashtable<K, V>::getCollision() {
    return collision;
}

//return the loadfactor of the hashtable
template<typename K, typename V>
double hashtable<K, V>::getLoadFactor() {
    return (double)sizes/(double)numBuckets;
}

//print out the data stored inside hashtable 
template<typename K,typename V>
void hashtable<K, V>::print() {
    hashNode<K, V>* ptr;
    for (int i = 0; i < numBuckets; i++) {
        if (bucketList[i]) {
            ptr = bucketList[i];
            while (ptr) {
                cout << ptr->getValue()->getUsrName() << endl;
                cout << ptr->getValue()->getBirthday() << endl;
                cout << ptr->getValue()->getEmail() << endl;
                ptr = ptr->getNext();
            }
        }
    }
}
