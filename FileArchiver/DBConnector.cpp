/* 
 * File:   DBConnector.cpp
 * Author: philipedwards
 * 
 * Created on 16 September 2015, 12:36 PM
 */

#include <string>
#include <fstream>

#include <mysql_connection.h>
#include <mysql_driver.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include "DBConnector.h"


using namespace std;

string decrypt(string s)
{
	for (unsigned int i = 0; i < s.size(); i++)
	{
		s[i] = s[i] - 1 - i%2;
	}

	return s;
}

DBConnector::DBConnector()
{
}

DBConnector::~DBConnector()
{
}

sql::Connection* DBConnector::GetConnection()
{
	sql::Connection* dbcon = NULL;
	sql::Driver* driver = NULL;
	
	// Get data for connection from file
	string host;
	string dbname;
	string user;
	string pw;

	ifstream ins("db.txt");
	getline(ins, dbname);
	getline(ins, user);
	getline(ins, pw);
	getline(ins, host);
	ins.close();	

	host = decrypt(host);
	dbname = decrypt(dbname);
	user = decrypt(user);
	pw = decrypt(pw);

	cout << "host: " << host << endl;
	cout << "user: " << user << endl;
	cout << "pw: " << pw << endl;
		
	// Connect to database
	try
	{
		driver = get_driver_instance();
		dbcon = driver->connect(host, user, pw); 
		dbcon->setSchema("redsquare");
	}
	catch (sql::SQLException&	e)
	{
		cout << "DBConnector Failed To Connect: " << endl;
		cout << e.what() << endl;
		cout << e.getErrorCode() << endl;
		cout << e.getSQLState() << endl;
	}
	
	return dbcon;
}
