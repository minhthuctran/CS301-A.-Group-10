#pragma once
#include "msg.h"

//msg default constructor
msg::msg(string  a, string b, string msg)
{
	sender = a;
	recipient = b;
	msg1 = msg;
}

//default destructor
msg::~msg()
{
}

//print out the sender,recipient, and message stored inside the msg object
void msg::printMSG()
{
	cout << "Sender: " << sender << "----->Recepient: " << recipient << endl;
	cout << "Message: " << msg1 << endl;
}

//return the sender of msg object
string msg::getSender()
{
	return sender;
}

//return the recipient of msg object
string msg::getRecipient()
{
	return recipient;
}
