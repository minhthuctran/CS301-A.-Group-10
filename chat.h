#pragma once
#include "user.h"
#include "hashtable.h"
#include <fstream>
#include <algorithm>

//wrapper class for the hashtbale and binary search tree 
//data will be added to both the hashtable and binary search tree

class chat {

private:
	hashtable<string, user*>* data = new hashtable<string, user*>();
	bst<user*>* userTree = new bst<user*>();

public:
	chat();
	void addUsr(user* a);
	void deleteUsr(string name);
	void sendMSG(user* sender, user* recipient, string msg);
	bool findUsr(string usrname);
	user* getUsr(string name);
	void printTree();
    void printEfficiency();
    void printHashtable();
	void quit();
	void loadDataRecord();
	void processSave();
	void rewriteRecord();
	void printSort();
	void inOrderPrint(bstNode<user*>* root);
};
