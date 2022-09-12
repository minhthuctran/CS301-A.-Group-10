#pragma once
#include <string>
#include "node.h"
#include "linkedlist.h"
#include "bst.h"
#include "hashtable.h"
#include "msg.h"

// this is just a draft of our user class
// user class will have a friendlist that is implemented by binary search tree which is sorted in alphabetic order
// user will also have a linkedlist that will saved its chat history

class user {
private:
	string usrname, password, birthday, email;
	bst<user*>* friendTree = new bst<user*>();
	linkedList<linkedList<msg*>*>* msgList = new linkedList<linkedList<msg*>*>();

public:
	user(string usrname, string password, string birthday, string email);
	~user();
	string getUsrName();
	string getPsw();
	string getBirthday();
	string getEmail();
	linkedList<linkedList<msg*>*>* getMsgList();
	bst<user*>* getFriendTree();
	void changePSW(string psw);
	bool pswMatch(string psw);
	void addFriend(user* user);
	void deleteFriend(user* user);
	void deleteChatHistory(string name);
	bool findFriend(user* user);
	void sendMSG(string recipient, msg* message);
	void receiveMSG(string sender, msg* message);
	void printFriendList();
	void printChatHistory(string name);
	void printUsrInfor();
    void inOrderPrint(bstNode<user*>* root);
	void printFriendTreeEffi();


};
