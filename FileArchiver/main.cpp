/*
 * File:   main.cpp
 * Author: philipedwards
 *
 * Created on 16 September 2015, 11:53 AM
 */

#include <QApplication>
#include "ProjectConstants.h"
#include "FileRecord.h"

#include <string>

#include "TestUtilities.h"
#include "FileArchiver.h"
#include "boost/lexical_cast.hpp"

using namespace std;

int main(int argc, char *argv[]) {
	// initialize resources, if needed
	// Q_INIT_RESOURCE(resfile);

	QApplication app(argc, argv);
	
	DropTables();
	CreateTables();
	
	RunTestCommitFileOneVersionRetrieve();
	RunTestCommitFileWithTwoVersionsRetrieveBoth();
	
	FileArchiver test;
	vector<FileRecord> files = test.GetFiles();
	
	for(unsigned int i = 0; i < files.size(); i++)
	{
		log(files[i].GetFilename() + " " + boost::lexical_cast<string>(files[i].GetCurrentVersionNumber()));
	}

	// create and show your widgets here

	//return app.exec();
	
	return 0;
}
