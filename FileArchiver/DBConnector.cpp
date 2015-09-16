/* 
 * File:   DBConnector.cpp
 * Author: philipedwards
 * 
 * Created on 16 September 2015, 12:36 PM
 */

#include <string>

#include "DBConnector.h"

using namespace std;

DBConnector::DBConnector()
{
}

DBConnector::DBConnector(const DBConnector& orig)
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

	// Connect to database
	try
	{	
			driver = get_driver_instance();
			dbcon = driver->connect(host, user, pw); 
	}
	catch (sql::SQLException &	e)
	{
			cout << "Initial Conection Failed: " << endl;
			cout << e.what() << endl;
			cout << e.getErrorCode() << endl;
			cout << e.getSQLState() << endl;
	}
	
	return dbcon;
}
