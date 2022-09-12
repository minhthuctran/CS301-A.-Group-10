#include "chat.h"

//default constructor
chat::chat()
{}

//Param: user a - user to add to data record
//user added into hashtable and bst tree
void chat::addUsr(user * a)
{
	data->add(a->getUsrName(), a);
	userTree->root = userTree->insert(userTree->root, a);
}

//Param: string name - username of account to be deleted
//Data deleted from hashtable and bst
void chat::deleteUsr(string name)
{
	
	user* tmp = getUsr(name);
	userTree->root = userTree->deleteNode(userTree->root, tmp);
	data->remove(name);
}

//Param: user* sender - account sending msg, user* recipient - account receiving msg, string text - msg
//Sends a message from to and from accounts
void chat::sendMSG(user* sender, user* recipient, string text)
{
	msg* message = new msg(sender->getUsrName(), recipient->getUsrName(), text);
	sender->sendMSG(recipient->getUsrName(), message);
	recipient->receiveMSG(recipient->getUsrName(), message);

}

//param: string usrname - usrname to be searched for
//returns whether or not such a username exists in the data records
bool chat::findUsr(string usrname)
{


	return data->hasKey(usrname);
}

//param: string usrname - usrname to be searched for
//returns a pointer to the user account being searched for
user * chat::getUsr(string name)
{
	transform(name.begin(), name.end(), name.begin(), ::tolower);
	try
	{
		if (!findUsr(name))
		{
			throw "Username doesn't exist";
		}
		
	}
	catch (const char* err)
	{
		cout << err << endl;
	}
    return data->get(name);
}

//print out the bst tree of the data records
void chat::printTree() {
	userTree->printTreeSpace(userTree->root, 0);
}

//print out the efficiency of the hashtable and binary search tree
void chat::printEfficiency(){
    cout<<"Hashtable using chaining:"<<endl;
    cout<<"number of collision of hashtable: "<<data->getCollision()<<endl;
    cout<<"load factor of hashtable: "<<data->getLoadFactor()<<endl<<endl;;
    cout<<"binary search tree"<<endl;
	userTree->printEfficiency();
}

//print out data in hash sequence
void chat::printHashtable(){
    data->print();
}

//load data in data records and load crash file if exists
void chat::loadDataRecord() {
	fstream in;
	in.open("datarecord.txt");
	if (!(in.is_open())) {
		cout << "File could not be opened." << endl;
		return;
	}
	string n, p, b, e;
	while (getline(in, n) && getline(in, p) && getline(in, b) && getline(in, e)) {
		transform(n.begin(), n.end(), n.begin(), ::tolower);
		user* newUsr = new user(n, p, b, e);
		addUsr(newUsr);
	}
	in.close();
	in.open("datarecordsave.txt");
	if (!(in.is_open())) {
		cout << "File could not be opened." << endl;
		return;
	}
	getline(in, n);
	if (n == "true") {
		//cant do this must be add or delete or modify
		in.close();
		processSave();
	}
}

//process a crash file in case program cloes before it had the chance to save to data records
void chat::processSave() {
	fstream in;
	in.open("datarecordsave.txt");
	if (!(in.is_open())) {
		cout << "File could not be opened." << endl;
		return;
	}
	string o, n, p, b, e;
	getline(in, o);
	while (getline(in, o)) {
		transform(o.begin(), o.end(), o.begin(), ::tolower);
		if (o == "add") {
			getline(in, n);
			getline(in, p);
			getline(in, b);
			getline(in, e);
			transform(n.begin(), n.end(), n.begin(), ::tolower);
			user* newUsr = new user(n, p, b, e);
			addUsr(newUsr);
		}
		else if (o == "delete") {
			getline(in, n);
			deleteUsr(n);
		}
		else if (o == "changepsw") {
			getline(in, n);
			getline(in, p);
			transform(n.begin(), n.end(), n.begin(), ::tolower);
			user* temp = getUsr(n);
			temp->changePSW(p);
		}
	}
	in.close();
	rewriteRecord();
	ofstream out;
	out.open("datarecordsave.txt");
	out << "false" << endl;
	out.close();
}

//write current data into data file
void chat::rewriteRecord() {
	ofstream out;
	out.open("datarecord.txt");
	userTree->printBFS(userTree->root, out);
	out.close();
}

//end the program and safely save to data file 
void chat::quit() {
	rewriteRecord();
	ofstream out;
	out.open("datarecordsave.txt");
	out << "false" << endl;
	out.close();
}

void chat::printSort() {
	inOrderPrint(userTree->root);
}

void chat::inOrderPrint(bstNode<user*>* root) {
	if (root) {
		inOrderPrint(root->getLeft());
		cout << root->getData()->getUsrName() << endl;
		cout << root->getData()->getBirthday() << endl;
		cout << root->getData()->getEmail() << endl << endl;
		inOrderPrint(root->getRight());
	}
}