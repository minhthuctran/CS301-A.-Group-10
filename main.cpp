//Minh Thuc Tran, Zihong Yi, and Christine Nguyen (Team 7)
// CIS22C Project: Message Application "Chat4Free" Friend list

#include <iostream>
#include <fstream>
#include <string>
#include "bst.h"
#include "linkedlist.h"
#include "msg.h"
#include "hashtable.h"
#include "chat.h"
#include <algorithm>

int main()
{
	//varable storing the current status of the program
	int choice;
	int choice2;
	int printChoice;
	bool run = true;
	bool exitSignIn = true;
	bool exitFriend = true;
	bool exitPrint = true;
	bool exitAccCreate = true;
	string username;
	string tmp;
	string password;
	string password2;
	string birthday;
	string email;
	string friendUser;
	string friendName = ("");
	string message;
	string goBack = ("goback");
	user* currentUser;
	user* currentFriend;
	user* tempFriend;
	chat* ct = new chat();

	//loading datas into the hashtable and binary search tree
	ct->loadDataRecord();

	//open save file for writing changes
	ofstream out;
	out.open("datarecordsave.txt");
	out << "true" << endl;

	//Enable to be able to go back to the while loop
mainMenu:
	while (run != false)
	{
		cout << "~~~~~Chat4Free~~~~~" << endl;
		cout << "1) Sign In" << endl;
		cout << "2) Create An Account" << endl;
		cout << "3) Delete An Account" << endl;
		cout << "4) Forget Password?" << endl;
		cout << "5) Print out the Data" << endl;
		cout << "6) Quit" << endl << endl;
		cout << "Input: ";
		cin >> choice;
		cout << endl;

		//Will continue to loop until the input stop failing and the input match with a switch case value
		while (cin.fail() || choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6)
		{
			cout << "Not a valid choice \n"
				<< "Please try again \n";

			//cin.clear will clear the error flags so that future inputs/outputs will work correctly.
			//cin.ignore will skip characters in the input.
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Input: ";
			cin >> choice;
			cout << endl;
		}

		switch (choice)
		{
		case 1:
			while (exitSignIn != false)
			{
				string passwordCorrect;
				cout << "Enter your username and password\n";
				cout << "Username: ";
				cin >> username;
				//Enable input of username to be not case sensitive
				transform(username.begin(), username.end(), username.begin(), ::tolower);
				cout << "Password: ";
				cin >> password;
				cout << endl;
				int count = 0;
				int count3 = 0;

				while (true)
				{
					//Find if the username is in the hash table
					if (!ct->findUsr(username)) {
						cout << "Username is not registered" << endl << endl;
						goto mainMenu;
					}
					//Loop if inputs is incorrect 5 times
					if (count >= 5) {
						cout << "You have too many failure attempts" << endl;
						cout << "Going back to main menu" << endl;
						goto mainMenu;
					}

					//Loop if username match with the password
					if (ct->getUsr(username)->pswMatch(password))
					{
						cout << "Sign in successful\n\n";
						//Get username from chat.h
						currentUser = ct->getUsr(username);
						break;
					}

					//Loop until inputs is wrong 5 times or username match with password correctly
					else {
						cout << "Sign in unsuccessful" << endl;

						cout << "You have " << 5 - count++ << "attempts left" << endl;
						cout << "Enter your username and password\n";
						cout << "Username: ";
						cin >> username;
						//Enable input of username to be not case sensitive
						transform(username.begin(), username.end(), username.begin(), ::tolower);
						cout << "Password: ";
						cin >> password;
						cout << endl;
					}
				}

				//1st submenu of the program
			subMenu:
				cout << "^^^^^Welcome: " << username << "^^^^^\n";
				cout << "1) Friend\n";
				cout << "2) Search Friend\n";
				cout << "3) Print Friend Tree Efficiency\n";
				cout << "4) Logout\n\n";
				cout << "Input: ";
				cin >> choice2;
				cout << endl;

				//Will continue to loop until the input stop failing and the input match with a switch case value
				while (cin.fail() || choice2 != 1 && choice2 != 2 && choice2 != 3 && choice2 != 4)
				{
					cout << "Not a valid choice \n"
						<< "Please try again \n";

					//cin.clear will clear the error flags so that future inputs/outputs will work correctly.
					//cin.ignore will skip characters in the input.
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Input: ";
					cin >> choice2;
					cout << endl;
				}

				switch (choice2)
				{
				case 1:
					//2nd submenu of the program
				sub2Menu:
					int choice3;
					while (exitFriend != false)
					{
						cout << "*****Friend List:*****" << endl;
						//Printing out the friend list
						currentUser->printFriendList();
						cout << endl;
						cout << "Please type in the name of your friend or\n"
							<< "\"goback\" to return to the previous menu.\n"
							<< "Input: ";
						cin >> friendName;
						//Enable input of username to be not case sensitive
						transform(friendName.begin(), friendName.end(), friendName.begin(), ::tolower);

						//If input is "goBack", return to the 1st submenu
						if (friendName == goBack)
						{
							cout << "\nReturning\n\n";
							goto subMenu;
						}
						cout << endl;

						//If input match with username in the hash table, retrieve the username
						if (ct->findUsr(friendName)) {
							tempFriend = ct->getUsr(friendName);
						}
						else {
							cout << "No username with that name\n\n";
							goto subMenu;
						}

						//Looping if username is found 
						if (currentUser->findFriend(tempFriend))
						{
							currentFriend = tempFriend;
							cout << "*****Friend: " << friendName << "*****\n";
							cout << "1) Text (Chat)\n";
							cout << "2) Review Chat History\n";
							cout << "3) Delete Chat History\n";
							cout << "4) Delete " << friendName << endl;
							cout << "5) Go Back\n\n";
							cout << "Input: ";
							cin >> choice3;
							cout << endl;

							//Will continue to loop until the input stop failing and the input match with a switch case value
							while (cin.fail() || choice3 != 1 && choice3 != 2 && choice3 != 3 && choice3 != 4 && choice3 != 5)
							{
								cout << "Not a valid choice \n"
									<< "Please try again \n";

								//cin.clear will clear the error flags so that future inputs/outputs will work correctly.
								//cin.ignore will skip characters in the input.
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
								cout << "Input: ";
								cin >> choice3;
								cout << endl;
							}

							switch (choice3)
							{
							case 1:
								cout << "-----Text(Chat)-----\n";
								cout << endl;
								cout << "Please enter your message:" << endl;

								//Enable for the inputs to be sentences long with spacing
								getline(cin, message);
								getline(cin, message);
								cout << endl;

								//Loop if friend delete current account from their list
								if (!currentFriend->findFriend(currentUser)) {
									cout << "sorry, this user has deleted you from his/her account!" << endl;
									cout << "you cannot send message." << endl << endl;
								}
								else {
									//Send message by using chat.cpp
									ct->sendMSG(currentUser, currentFriend, message);
									cout << endl;
									//Print chat history between the current two account using user.cpp
									currentUser->printChatHistory(friendName);
									cout << endl;
								}
								goto sub2Menu;
								break;

							case 2:
								cout << "-----Chat History-----\n";
								cout << endl;
								cout << "friendName" << friendName << endl;
								//Print chat history between the current two account using user.cpp
								currentUser->printChatHistory(friendName);
								cout << endl;
								goto sub2Menu;
								break;

							case 3:
								cout << "Delete chat history successful\n\n";
								//Delete chat history between the current two account using user.cpp
								currentUser->deleteChatHistory(friendName);

								goto sub2Menu;
								break;

							case 4:
								cout << "Delete friend successful\n\n";
								//Delete both username and chat history using user.cpp
								currentUser->deleteChatHistory(friendName);
								currentUser->deleteFriend(currentFriend);

								goto subMenu;
								break;
							case 5:
								cout << "Going back to friend's menu\n\n";
								goto subMenu;
								break;

							default: {}
							}
						}
						else
						{
							cout << "This user is not your friend yet\n\n";
							goto subMenu;
						}
					}

				case 2:
					cout << "*****Search Friend*****\n";
					cout << "Username:";
					cin >> tmp;
					//Enable input of username to be not case sensitive
					transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
					cout << endl;
					//Loop if username is in the hash table
					if (ct->findUsr(tmp)) {
						cout << "This is " << tmp << "'s basic information:" << endl;
						//Retrieve and print username's information
						ct->getUsr(tmp)->printUsrInfor();

						cout << "If you want to add this user, enter 1; if not enter 0" << endl;
						cin >> choice3;
						cout << endl;
						if (choice3) {
							//Loop if username is the current account's username
							if (ct->getUsr(tmp) == currentUser) {
								cout << "Cannot add yourself as friend" << endl << endl;
							}
							else {
								//Loop if username is already added as friend
								if (currentUser->findFriend(ct->getUsr(tmp))) {
									cout << "He/She are already your friend" << endl << endl;
								}
								else {
									//Use user.cpp to add username as friend to current account
									currentUser->addFriend(ct->getUsr(tmp));
									cout << tmp << " has been added to your friendlist!" << endl << endl;
								}
							}
						}
						else {
							cout << "return to the friendMenu" << endl << endl;
						}
					}
					else {
						cout << "Sorry, no account with username " << tmp << " is found :(" << endl << endl;
					}
					goto subMenu;
					break;
				case 3:
					//Print out friend tree efficiency 
					currentUser->printFriendTreeEffi();
					goto subMenu;
					break;

				case 4:
					cout << "Logging out\n\n";
					goto mainMenu;
					break;

				default: {}
				}
			}

		case 2:
			while (exitAccCreate != false)
			{
				cout << "*****Create An Account*****\n";
				cout << "Account Creation:\n\n";
				cout << "1) Username: ";
				cin >> username;
				//Enable input of username to be not case sensitive
				transform(username.begin(), username.end(), username.begin(), ::tolower);
				//Looping until username inputed is not already in the hash table
				while (ct->findUsr(username)) {
					cout << "Name is already taken" << endl;
					cout << "1) Username: ";
					cin >> username;
					//Enable input of username to be not case sensitive
					transform(username.begin(), username.end(), username.begin(), ::tolower);
				}
				cout << "2) Birthday: ";
				cin >> birthday;
				cout << "3) Email address: ";
				cin >> email;
				//Enable input of email to be not case sensitive
				transform(email.begin(), email.end(), email.begin(), ::tolower);
				cout << "4) Password: ";
				cin >> password;
				cout << "5) Confirm password: ";
				cin >> password2;

				//Loop if password match with 2nd password
				if (!password.compare(password2))
				{
					//Bind username to password, birthday, and email
					user* newUsr = new user(username, password, birthday, email);
					//Add username to hash table
					ct->addUsr(newUsr);
					// Add account's info to the output file
					out << "add" << endl << username << endl << password << endl << birthday << endl << email << endl;
					cout << "\nCongratulation!" << endl;
					cout << "You can sign in now.\n\n";
					goto mainMenu;
				}
				int count2 = 0;

				//Looping until the inputs is wrong 3 times or 1st password match correctly with 2nd password entered
				while (true)
				{
					if (count2 >= 3) {
						cout << "\nYou have too many failure attempts" << endl;
						cout << "Going back to main menu\n\n";
						goto mainMenu;
					}
					else {
						cout << "\nPassword does not match.\n"
							<< "You have " << 3 - count2++ << " attempts left\n"
							<< "Please try again. \n\n";
						cout << "Confirm password: ";
						cin >> password2;
					}

					if (!password.compare(password2))
					{
						user* newUsr = new user(username, password, birthday, email);
						ct->addUsr(newUsr);
						out << "add" << endl << username << endl << password << endl << birthday << endl << email << endl;
						cout << "\nCongratulation!" << endl;
						cout << "You can sign in now\n\n";
						goto mainMenu;
					}
				}
			}
			break;

		case 3:
			cout << "*****Delete An Account*****\n";

			while (exitSignIn != false)
			{
				string passwordCorrect;
				cout << "Enter your username and password\n";
				cout << "Username: ";
				cin >> username;
				//Enable input of username to be not case sensitive
				transform(username.begin(), username.end(), username.begin(), ::tolower);
				cout << "Password: ";
				cin >> password;
				cout << endl;
				int count = 0;
				int count3 = 0;

				//Looping until inputs is wrong 5 times or username is correctly match with password 
				while (true)
				{
					//Loop if username is not in the hash table
					if (!ct->findUsr(username)) {
						cout << "Username is not registered" << endl << endl;
						goto mainMenu;
					}
					if (count >= 5) {
						cout << "You have too many failure attempts" << endl;
						cout << "Going back to main menu" << endl;
						goto mainMenu;
					}

					if (ct->getUsr(username)->pswMatch(password))
					{
						cout << "Delete successful\n\n";
						ct->deleteUsr(username);
						out << "delete" << endl << username << endl;
						goto mainMenu;
					}

					else {
						cout << "Delete unsuccessful" << endl;

						cout << "You have " << 5 - count++ << "attempts left" << endl;
						cout << "Enter your username and password\n";
						cout << "Username: ";
						cin >> username;
						transform(username.begin(), username.end(), username.begin(), ::tolower);
						cout << "Password: ";
						cin >> password;
						cout << endl;
					}
				}
			}
			break;

		case 4:
			cout << "*****Forget Password?*****\n";
			cout << "Please input username, email, and birthday\n\n";
			cout << "Username: ";
			cin >> username;
			//Enable input of username to be not case sensitive
			transform(username.begin(), username.end(), username.begin(), ::tolower);
			cout << "Email address: ";
			cin >> email;
			//Enable input of email to be not case sensitive
			transform(email.begin(), email.end(), email.begin(), ::tolower);
			cout << "Birthday: ";
			cin >> birthday;
			cout << endl;

			//Loop if username is in the hash table
			if (ct->findUsr(username)) {
				//Retrive username
				currentUser = ct->getUsr(username);
				//Email correctly match with username
				if (currentUser->getEmail() == email) {
					//Birthday correctly match with username
					if (currentUser->getBirthday() == birthday) {
						cout << "Enter your new password:" << endl;
						cin >> password;
						cout << "Confirm your new password:" << endl;
						cin >> password2;

						//Loop to replace password with a new one in the hash table
						if (password == password2) {
							currentUser->changePSW(password);
							out << "changepsw" << endl << currentUser->getUsrName() << endl << password << endl;
						}
						else {
							cout << "\nPassword does not match" << endl;
						}
					}
					else {
						cout << "Information does not match" << endl;
					}
				}
				else {
					cout << "Information does not match" << endl;
				}
			}
			else {
				cout << "User doesn't exist" << endl;
			}
			cout << endl;
			goto mainMenu;
			break;
		case 5:
			exitPrint = false;
			while (!exitPrint) {
				cout << "*****Print Data****\n";
				cout << "1) Print Tree\n";
				cout << "2) Print Hashtable data\n";
				cout << "3) Print Efficiency\n";
				cout << "4) Print Sorted data\n";
				cout << "5) Go back\n\n";
				cout << "Input: ";
				cin >> printChoice;
				cout << endl;

				while (cin.fail() || printChoice != 1 && printChoice != 2 && printChoice != 3 && printChoice != 4 && printChoice != 5)
				{
					cout << "Not a valid choice \n"
						<< "Please try again \n";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Input: ";
					cin >> printChoice;
					cout << endl;
				}

				switch (printChoice) {
				case 1:
					//print out the data stored in binary search tree
					cout << "Data stored in binary search tree:" << endl;
					ct->printTree();
					cout << endl;
					break;
				case 2:
					//print out the data stored in hashtable
					cout << "Data stored in hashtable using chaining:" << endl << endl;
					ct->printHashtable();
					cout << endl;
					break;
				case 3:
					//print out the efficiency of the program
					cout << "Efficiency of the data structure:" << endl << endl;
					ct->printEfficiency();
					cout << endl;
					break;
				case 4:
					//print out sorted list of users
					cout << "Sorted data list from bst:" << endl << endl;
					ct->printSort();
					cout << endl;
					break;
				case 5:
					exitPrint = true;
					break;
				}
			}
			break;

		case 6:
			//Exiting the while loop
			cout << "Exiting Chat4Free" << endl;
			run = false;
			break;

		default: {}
		}
	}
	//Close the output file and end the program
	out.close();
	ct->quit();
	system("pause");
	return 0;
}
