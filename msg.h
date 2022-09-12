#pragma once
#include <iostream>
#include <string>
using namespace std;
// this is just a draft of msg class
// msg class is for storing the sender, recipient, and content of information
class msg {

	string sender;
	string recipient;
	string msg1;

public:
	msg(string a, string b, string msg);
	~msg();
	void printMSG();

	string getSender();

	string getRecipient();

};
