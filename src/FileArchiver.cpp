// File: FileArchiver.cpp
// Author: Thomas Nixon

#include "mysql_connection.h"
#include "mysql_driver.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <string>
#include "FileArchiver.h"

using namespace std;

// Prepares connection
FileArchiver::FileArchiver()
{
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

	host    = decrypt(host);
	dbname    = decrypt(dbname);
	user    = decrypt(user);
	pw    = decrypt(pw);

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
	
}

FileArchiver::~FileArchiver()
{
  Close();
}

bool FileArchiver::Exitsts(std::string filename)
{
  try
  {
  	// Run Query
  	sql::Statement *stmt = dbcon->createStatement();;
  	sql::ResultSet *rs = stmt->executeQuery("select * from redsquare.somewhere where someID = "+ filename);
  	
  	// Output Results
  	while(rs->next())
  		cout << rs->getString(1) << endl;
  
  	delete rs;
  	delete stmt;
  }
  catch (sql::SQLException &	e)
  {
  	cout << "ERROR: " << endl;
  	cout << e.what() << endl;
  	cout << e.getErrorCode() << endl;
  	cout << e.getSQLState() << endl;
  }
}

bool FileArchiver::Compare(std::string filename)
{

}

bool FileArchiver::Insert(std::string filename, std::string comment)
{

}

VersionRec FileArchiver::GetVersionInfo(std::string filename)
{
  try
  {
  	// Run Query
  	sql::Statement *stmt = dbcon->createStatement();;
  	sql::ResultSet *rs = stmt->executeQuery("select * from redsquare.comments");
  	
  	// Output Results
  	while(rs->next())
  		cout << rs->getString(1) << endl;
  
  	delete rs;
  	delete stmt;
  }
  catch (sql::SQLException &	e)
  {
  	cout << "ERROR: " << endl;
  	cout << e.what() << endl;
  	cout << e.getErrorCode() << endl;
  	cout << e.getSQLState() << endl;
  }
}

bool FileArchiver::Update(std::string filename)
{

}

VersionRec FileArchiver::GetLastVersionInfo(std::string filename)
{
  try
  {
  	// Run Query
  	sql::Statement *stmt = dbcon->createStatement();;
  	sql::ResultSet *rs = stmt->executeQuery("select * from redsquare.comments");
  	
  	// Output Results
  	while(rs->next())
  		cout << rs->getString(1) << endl;
  
  	delete rs;
  	delete stmt;
  }
  catch (sql::SQLException &	e)
  {
  	cout << "ERROR: " << endl;
  	cout << e.what() << endl;
  	cout << e.getErrorCode() << endl;
  	cout << e.getSQLState() << endl;
  }
}

bool FileArchiver::RetrieveVersion(int versionnum, std::string filebname, std::string retrievedname)
{
  try
  {
  	// Run Query
  	sql::Statement *stmt = dbcon->createStatement();;
  	sql::ResultSet *rs = stmt->executeQuery("select * from redsquare.comments");
  	
  	// Output Results
  	while(rs->next())
  		cout << rs->getString(1) << endl;
  
  	delete rs;
  	delete stmt;
  }
  catch (sql::SQLException &	e)
  {
  	cout << "ERROR: " << endl;
  	cout << e.what() << endl;
  	cout << e.getErrorCode() << endl;
  	cout << e.getSQLState() << endl;
  }
}

void FileArchiver::Close()
{
	dbcon->close();
	delete dbcon;
}

string FileArchiver::decrypt(string s)
{
	for (int i = 0; i < s.size(); i++)
		s[i] = s[i] - 1 - i%2;

	return s;
}
