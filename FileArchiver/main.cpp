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
using namespace std;

int main(int argc, char *argv[]) {
	// initialize resources, if needed
	// Q_INIT_RESOURCE(resfile);

	QApplication app(argc, argv);
	
	FileRecord newFile;
	bool bSuccess = newFile.CreateFile("MurmurHash3.cpp");
	
	string logMessage = "The result was: ";
	if(bSuccess)
	{
		logMessage += "Success!";
	}
	else
	{
		logMessage += "The nixon snake has failed";
	}
	
	log(logMessage);

	// create and show your widgets here

	//return app.exec();
	
	return 0;
}
