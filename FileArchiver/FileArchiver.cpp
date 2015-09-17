// File: FileArchiver.cpp
// Author: Thomas Nixon

#include "mysql_connection.h"
#include "mysql_driver.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "FileArchiver.h"
#include "DBConnector.h"
#include "VersionRecord.h"

#include "MurmurHash3.h"

using namespace std;

// Prepares connection
FileArchiver::FileArchiver()
{
    dbcon = DBConnector::GetConnection();
}

// Closes database
FileArchiver::~FileArchiver()
{
    Close();
}

// Checks the existence of a record 
bool FileArchiver::Exists(std::string filename)
{
    int count = 0;
    try
    {
        // Run Query
        sql::Statement *stmt = dbcon->createStatement();;
        sql::ResultSet *rs = stmt->executeQuery("select count(*) from redsquare.filerec where filename = '" + filename + "'");

        // Output Results
        while(rs->next())
            count = rs->getInt(1);

        delete rs;
        delete stmt;
    }
    catch (sql::SQLException &e)
    {
        cout << "ERROR: " << endl;
        cout << e.what() << endl;
        cout << e.getErrorCode() << endl;
        cout << e.getSQLState() << endl;
    }

    return count;
}

// Compares a file with one in the database. Hashes file and then compares db hash.
bool FileArchiver::Compare(std::string filename)
{    
    // Get data from file
    int length = 0;
    char* data = GetDataFromFile(filename, length);

    // Hash the file data
    unsigned int newHash = 0;
    MurmurHash3_x86_32(data, length, 46, &newHash);
    
    // Delete data created
    delete data;

    // get hash from db of file
    unsigned int cmpHash = 0;
    try
    {
        // Run Query
        sql::Statement *stmt = dbcon->createStatement();;
        sql::ResultSet *rs = stmt->executeQuery("select curhash from redsquare.filerec where filename = '" + filename + "'");

        // Output Results
        while(rs->next())
            cmpHash = rs->getInt(1);

        delete rs;
        delete stmt;
    }
    catch (sql::SQLException &e)
    {
        cout << "ERROR: " << endl;
        cout << e.what() << endl;
        cout << e.getErrorCode() << endl;
        cout << e.getSQLState() << endl;
    }
       
    // compare the hashes
    return (newHash == cmpHash);;
}

bool FileArchiver::Insert(std::string filename, std::string comment)
{
    // Get data from file
    int length = 0;
    char* data = GetDataFromFile(filename, length);

    // Hash the file data
    unsigned int newHash = 0;
    MurmurHash3_x86_32(data, length, 46, &newHash);
    
    try
    {
        // Run Query
        sql::Statement *stmt = dbcon->createStatement();;
        //sql::ResultSet *rs = stmt->executeQuery("insert into redsquare.filerec(filename, curhash) values('" + filename + "'," + newHash + ")");

        // Check record was inserted, somehow
        //while(rs->next())
        //    cmpHash = rs->getInt(1);

        //delete rs;
        delete stmt;
    }
    catch (sql::SQLException &e)
    {
        cout << "ERROR: " << endl;
        cout << e.what() << endl;
        cout << e.getErrorCode() << endl;
        cout << e.getSQLState() << endl;
    }  
    
    // Delete data created
    delete data;
       
    return false;
}

VersionRecord FileArchiver::GetVersionInfo(std::string filename)
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
    //TODO: add logic here
    return false;
}

VersionRecord FileArchiver::GetLastVersionInfo(std::string filename)
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

char* FileArchiver::GetDataFromFile(string filename, int &length)
{
    // Prepare variables
    char* data = 0; 
    length = 0;
    
    // read file in
    ifstream ins(filename.c_str());
    
    // Catch problem with file
    if (!ins.good())
    {
        cout << "file is not good." << endl;
        return NULL;
    }
    
    // Find length of data
    ins.seekg(0,ios::end);
    length = ins.tellg();
    ins.seekg(0,ios::beg);

    // Store file in data
    data = new char[length+1];
    ins.read(data, length);
    ins.close();
    
    return data;
}