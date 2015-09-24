/*
 * File:   MyWindow.cpp
 * Author: io447
 *
 * Created on 21 September 2015, 12:36 PM
 */

#include "MyWindow.h"

MyWindow::MyWindow() {
    widget.setupUi(this);
}

MyWindow::~MyWindow() {
}

//file selection
void MyWindow::SelectFile() {
    
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
   /* Use standard Qt FileDialog allowing user to enter a filename
   Display name of file as chosen by user
   Invoke FileArchiver::exists() member function via FileArchiver object
    If a record already exists
      Invoke this->retrieveVersionDataForFile() to get collection of VersionInfoRecords and enable
            Save
    else
     Invoke this->createFirstVersion() to create initial version of file in persistent storage
    
    ---RetrieveVersionDataForFile()
    Clear any existing data in table model used to display version database
    Invoke FileArchiver::getVersionInfo(filename) via FileArchiver object
    Repopulate table model with VersionInfoRecords displayed
    Adjust display
   
    * 
    -----createFirstVersion()
    Use dialog to get comment to go with this initial version
    Invoke FileArchiver::insertNew()
    Invoke this->retrieveVersionDataForFile()
     
    */
}

void MyWindow::SaveCurrent()
{
    /*
       Invoke FileArchiver::differs(filename) via FileArchiver object
   If the files are the same, notify the user and return.
   Use dialog to get comment to go with new version
   Invoke FileArchiver::update(filename,comment) via FileArchiver object
   Invoke this->retrieveVersionDataForFile() */
}

void MyWindow::ShowComment()
{
    /*
          Invoke FileArchiver::getComment(filename,version-number) via FileArchiver object.
  Display comment using standard Qt “Information Dialog” */
}

void MyWindow::SetReferenceVersion()
{
    /*
             Use a Qt confirmation dialog to confirm that user wishes this destructive action
   Use the GetComment dialog to get a comment to go with the new reference version 
   Invoke FileArchiver::setReference(filename, version-number, comment) via 
          FileArchiver object.   
   Invoke this->retrieveVersionDataForFile() */
}




/*Retrieve version
   Use RetrievForm dialog to get details of where retrieved file to be placed
   Invoke FileArchiver::retrieveVersion(version-number, filename, retrievedname) via 
          FileArchiver object*/

/*Selection of Entry in version table display
  Record in instance members details of the row selected and the actual version number that
      corresponds to the selected row*/