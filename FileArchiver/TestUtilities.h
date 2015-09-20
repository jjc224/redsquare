/* 
 * File:   TestUtilities.h
 * Author: philipedwards
 *
 * Created on 21 September 2015, 8:41 AM
 */

#ifndef TESTUTILITIES_H
#define	TESTUTILITIES_H

#include <string>
#include <mysql_connection.h>
#include <mysql_driver.h>

void DropTables();
void CreateTables();

void ExecuteSQLFile(std::string path);

bool ExecuteUpdateStatement(sql::Connection* dbcon, std::string sqlstatement);

void CommitFileWithOneVersion(std::string path);

void RunTestCommitFileOneVersion();

#endif	/* TESTUTILITIES_H */

