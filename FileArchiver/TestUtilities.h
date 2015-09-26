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

void createFile(int seed, std::string filename, int length);
void appendFile(int seed, std::string filename, int length);

void DropTables();
void CreateTables();

void ExecuteSQLFile(std::string path);

bool ExecuteUpdateStatement(sql::Connection* dbcon, std::string sqlstatement);

void CommitFileWithOneVersion(std::string path);
void CommitFileWithTwoVersions();

void RunTestCommitFileOneVersion();
void RunTestCommitFileOneVersionRetrieve();
void RunTestCommitFileWithTwoVersionsRetrieveBoth();

void RunTestPurge();

#endif	/* TESTUTILITIES_H */

