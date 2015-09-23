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

using namespace std;

int main(int argc, char *argv[]) {
	// initialize resources, if needed
	// Q_INIT_RESOURCE(resfile);

	QApplication app(argc, argv);
	
	RunTestCommitFileWithTwoVersionsRetrieveBoth();

	// create and show your widgets here

	//return app.exec();
	
	return 0;
}
