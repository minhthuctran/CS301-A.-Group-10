#pragma once
#include "user.h"

user::user(string name, string psw, string birth, string eml) {
	usrname = name;
	password = psw;
	birthday = birth;
	email = eml;
}

user::~user() {

}

linkedList<linkedList<msg*>*>* user::getMsgList() {
	return msgList;
}
bst<user*>* user::getFriendTree()
{
	return friendTree;
}
string user::getUsrName() {
	return usrname;
}
string user::getPsw() {
	return password;
}

string user::getBirthday() {
	return birthday;
}
string user::getEmail() {
	return email;
}
void user::changePSW(string psw) {
	password = psw;
}

bool user::pswMatch(string psw) {
	if (password == psw) {
		return true;
	}
	return false;
}

void user::addFriend(user* user) {
	friendTree->root = friendTree->insert(friendTree->root, user);
	user->getFriendTree()->root = user->getFriendTree()->insert(user->getFriendTree()->root, this);
}

void user::deleteFriend(user* user) {
	friendTree->root = friendTree->deleteNode(friendTree->root, user);
}

void user::deleteChatHistory(string name)
{
	linkedList<msg*>* curr = nullptr;

	for (int i = 0; i < msgList->count(); i++) {
		if (msgList->getData(i)->getData(0) != nullptr&&msgList->getData(i)->getData(0)->getRecipient() == usrname) {
			if (msgList->getData(i)->getData(0)->getSender() == name) {
				curr = msgList->getData(i);
				break;
			}
		}
		else {
			if (msgList->getData(i)->getData(0) != nullptr&&msgList->getData(i)->getData(0)->getRecipient() == name) {
				curr = msgList->getData(i);
				break;
			}
		}
	}
	if (curr) {
		
		for (int i = 0; i < curr->count(); i++) {
			curr->setData(i, nullptr);
		}
	}
		
	
}

bool user::findFriend(user* user) {
	return friendTree->search(user);
}


void user::sendMSG(string recipient, msg * message)
{
	linkedList<msg*>* curr = nullptr;

	for (int i = 0; i < msgList->count(); i++) {
	
		if (msgList->getData(i)->getData(0) != nullptr&&msgList->getData(i)->getData(0)->getSender() == recipient) {
			cout <<"sender " <<msgList->getData(i)->getData(0)->getSender() << endl;
			curr = msgList->getData(i);
			break;
		}
		
		if (msgList->getData(i)->getData(0) != nullptr&&msgList->getData(i)->getData(0)->getRecipient() == recipient) {

			cout <<"recipient "<<msgList->getData(i)->getData(0)->getRecipient() << endl;
			curr = msgList->getData(i);
			break;
		}
	}

	if (!curr) {
		linkedList<msg*>* tmp = new linkedList<msg*>();
		tmp->add(0, message);
		msgList->add(msgList->count(), tmp);

	}
	else {

		curr->add(curr->count(), message);
	}

}
void user::receiveMSG(string sender, msg * message)
{
	linkedList<msg*>* curr = nullptr;
	for (int i = 0; i < msgList->count(); i++) {
		if (msgList->getData(i)->getData(0) != nullptr&&msgList->getData(i)->getData(0)->getRecipient() == sender) {
			curr = msgList->getData(i);
			break;
		}
		if (msgList->getData(i)->getData(0) != nullptr&&msgList->getData(i)->getData(0)->getSender() == sender) {

			curr = msgList->getData(i);
			break;
		}


	}

	if (!curr) {

		linkedList<msg*>* tmp = new linkedList<msg*>();
		tmp->add(0, message);
		msgList->add(msgList->count(), tmp);
	}
	else {

		curr->add(curr->count(), message);
	}
}

void user::printFriendList() {
	inOrderPrint(friendTree->root);
}

void user::printChatHistory(string name) {
	linkedList<msg*>* curr = nullptr;

	for (int i = 0; i < msgList->count(); i++) {
		if (msgList->getData(i)->getData(0) != nullptr&&msgList->getData(i)->getData(0)->getRecipient() == usrname) {
			
			if (msgList->getData(i)->getData(0)->getSender() == name) {
				curr = msgList->getData(i);
				break;
			}
		}
		else {
			if (msgList->getData(i)->getData(0) != nullptr&&msgList->getData(i)->getData(0)->getRecipient() == name) {
				curr = msgList->getData(i);
				break;
			}
		}
	}
	if (!curr) {
		cout << "you don't have any chat history with this friend!" << endl;
	}
	else {

		for (int i = 0; i < curr->count(); i++) {
			
			curr->getData(i)->printMSG();
		}
	}
}

void user::printUsrInfor() {
	cout << "user name:" << usrname << endl;
	cout << "birthday:" << birthday << endl;
}

void user::inOrderPrint(bstNode<user*>* root) {
	if (root) {
		inOrderPrint(root->getLeft());
		cout << root->getData()->getUsrName() << endl;
		inOrderPrint(root->getRight());
	}
}

void user::printFriendTreeEffi()
{
	friendTree->printEfficiency();
}
