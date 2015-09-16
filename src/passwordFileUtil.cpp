// File: FileArchiver.cpp
// Author: Philip Edwards

#include <string>
#include <fstream>

using namespace std;

string decrypt(string s)
{
	for (int i = 0; i < s.size(); i++)
		s[i] = s[i] - 1 - i%2;

	return s;
}

string encrypt(string s)
{
	for (int i = 0; i < s.size(); i++)
		s[i] = s[i] + 1 + i%2;

	return s;
}

int main(int argc, char* argv[])
{
	string dbname;
	string user;
	string pw;
	string host;

	ifstream ins("db-unencrypted.txt");
	getline(ins, dbname);
	getline(ins, user);
	getline(ins, pw);
	getline(ins, host);
	
	ofstream out("db.txt");
	out << encrypt(dbname) << endl;
	out << encrypt(user) << endl;
	out << encrypt(pw) << endl;
	out << encrypt(host) << endl;
	
	out.close();
	ins.close();
}

