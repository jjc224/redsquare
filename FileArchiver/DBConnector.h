/* 
 * File:   DBConnector.h
 * Author: philipedwards
 *
 * Created on 16 September 2015, 12:36 PM
 */

#ifndef DBCONNECTOR_H
#define	DBCONNECTOR_H

#include <mysql_connection.h>
#include <mysql_driver.h>

class DBConnector
{
public:
	DBConnector();
	virtual ~DBConnector();
	
	static sql::Connection* GetConnection();
private:

};

#endif	/* DBCONNECTOR_H */

