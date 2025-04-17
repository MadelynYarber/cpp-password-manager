#include "hashtable.h"
#include "passserver.h"

using namespace std;
using namespace cop4530;

void Menu()
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}

int main()
{
int hashSize = 0;
char userChoice;
string filename;
string username;
string pass;
bool keepGoing = true;

cout << "Enter preferred hash table capacity (integer): ";
cin >> hashSize;

if (hashSize < 2)
{
	cout << "** input is too small" << endl;
	cout << "set to default capacity" << endl;
	hashSize = 101;
}

PassServer server(hashSize);

cout << server.get_prime_below(hashSize) << endl;
//cout << prime_below(hashSize) << endl;

while (keepGoing)
{
	Menu();
	cin >> userChoice;
	//cout << endl;
	cout << "choice: " << userChoice << endl;

	if (userChoice == 'l') //load from file
	{
		cout << "Enter password file name to load from: ";
		cin >> filename;
		if(server.load(filename.c_str()) == false)
		{
			cout << "Error: Cannot open file " << filename;
		}
		cout << endl;
	}
	else if (userChoice == 'a') // add user
	{
		cout << "Enter username: ";
		cin >> username;
		cout << "Enter password: ";
		cin >> pass;
		if(server.addUser(make_pair(username, pass)) == true)
		{	
			cout << endl;
			cout << "User " << username << " added.";
		}
		else if (server.addUser(make_pair(username, pass)) == false)
		{
			cout << "*****Error: User already exists. Could not add user.";
		}
		cout << endl;		
	}
	else if (userChoice == 'r') //remove user
	{		
		cout << "Enter username: ";
		cin >> username;
		if(server.removeUser(username) == true)
		{
			cout << "User " << username << " deleted.";
		}
		else
		{
			cout << "*****Error: User not found. Could not delete user";
		}
		cout << endl;	
	}
	else if (userChoice == 'c') //change user password
	{
		string newPass;
		cout << "Enter username: ";
		cin >> username;
		cout << "Enter password: ";
		cin >> pass;
		cout << endl;
		cout << "Enter new password: ";
		cin >> newPass;
		cout << endl;
		if(server.changePassword(make_pair(username, pass), newPass) == true)
		{
		cout << "Password changed for user " << username;
		}
		else
		{	
			cout << "*****Error: Could not change user password";
		}
		cout << endl;		
	}
	else if (userChoice == 'f') //find user
	{
		cout << "Enter username: ";
		cin >> username;
		cout << endl;
		if(server.find(username) == true)
		{	
			cout << "User '" << username << "' found.";
		}
		else
		{	
			cout << "User '" << username << "' not found.";
		}
		cout << endl;		
	}
	else if (userChoice == 'd') //dump hashtable
	{
		server.dump();
	}
	else if (userChoice == 's') //hashtable size
	{
		cout << "Size of hashtable: " << server.size() << endl;	
	}
	else if (userChoice == 'w') //write to password file
	{
		cout << "Enter password file name to write to: ";
		cin >> filename;
		if(server.write_to_file(filename.c_str()) == false)
			{
			cout << "Error: File write failure" << endl;
			}
	}
	else if (userChoice == 'x') //exit
	{
		//cout << "exit program" << endl;
		keepGoing = false;
	}
	else
	{
		cout << endl;
		cout << "*****Error: Invalid entry. Try again." << endl;
	}
}	

return 0;

}	
