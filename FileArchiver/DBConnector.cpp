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

#include "boost/lexical_cast.hpp"

#include "DBConnector.h"
#include "ProjectConstants.h"


using namespace std;

static sql::Connection* dbcon = NULL;
static sql::Driver* driver = NULL;
static bool bInitialised = false;

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
	//sql::Connection* dbcon = NULL;
	//sql::Driver* driver = NULL;
	if(bInitialised != false && dbcon != NULL)
	{
		return dbcon;
	}
	
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

	log("host: " + host);
	log("user: " + user);
	log("pw: " + pw);
		
	// Connect to database
	try
	{
		driver = get_driver_instance();
		dbcon = driver->connect(host, user, pw); 
		dbcon->setSchema(dbname);
		bInitialised = true;
	}
	catch (sql::SQLException&	e)
	{
		log("ERROR: ");
		log(e.what());
		log(boost::lexical_cast<string>(e.getErrorCode()));
		log(e.getSQLState());
	}
	
	//dbcon->setTransactionIsolation(sql::TRANSACTION_READ_UNCOMMITTED);
	return dbcon;
}
