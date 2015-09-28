/*
 * File:   MyWindow.cpp
 * Author: io447
 *
 * Created on 21 September 2015, 12:36 PM
 */
#include <QFileDialog>
#include <QApplication>
#include <iostream>
#include <string>

#include "MyWindow.h"
#include "FileArchiver.h"
#include "FileRecord.h"

MyWindow::MyWindow() {
    widget.setupUi(this);
    
    //connect SelectFile() to selectFileBttn
    connect(widget.selectFileBttn, SIGNAL(clicked()), this, SLOT(SelectFile()));
    connect(widget.retrieveVersionBttn, SIGNAL(clicked()), this, SLOT(RetrieveVersion()));
}

MyWindow::~MyWindow() {
    
    delete getCommentWindow;
}

//file selection
void MyWindow::SelectFile() {
    
    //declare new select file dialog
    QFileDialog dialog(this);
    //set mode to existing file
    dialog.setFileMode(QFileDialog::ExistingFile);
    //set view mode to detail
    dialog.setViewMode(QFileDialog::Detail);
    
    QStringList fileNames;
    //QString fileName;
    if (dialog.exec())
    {
        //dialog.selectFile(fileName);
         fileNames = dialog.selectedFiles();
    }

    //Display name of file as chosen by user
    QString fileName;
    if(!fileNames.isEmpty())
    {
        fileName = fileNames[0];
        widget.selectFilePath->setText(fileName);
    }
    
    //convert to std string
    std::string stdFileName;
    stdFileName = fileName.toStdString();
    
    
    //need db connection to test this part
    /*
    try
    {
        FilePtr currentPath = new FileArchiver;
    }
    catch(std::bad_alloc)
    {
        // Message dialog with something like "Error: unable to allocate memory. Terminating."
        exit(1);
    }*/
    
    //for now not catching exception bad_alloc
    FilePtr currentPath = new FileArchiver;
    
    /*
    //If a record already exists
    if(currentPath->Exists(stdFileName))
    {
        //VersionRecord record;
        //record = currentPath->GetFile(stdFileName).GetVersionFileContents()
        //Invoke this->retrieveVersionDataForFile() to get collection of VersionInfoRecords 

        //and enable Save
    }    
    else
    {
       // Invoke this->createFirstVersion() to create initial version of file in persistent storage
        //CreateFirstVersion(stdFileName);

        
    }
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

void MyWindow::CreateFirstVersion(std::string fileName)
{
    //Use GetCommentForm dialog to go with this initial version
    getCommentWindow = new GetCommentForm(); // Be sure to destroy you window somewhere
    getCommentWindow->show();
    
    //--->create function in GetCommentForm
        //QString comment = widget.textGetCommentForm->toPlainText();
    
    
    //create new record --> catch bad_alloc
    FilePtr file = new FileArchiver;
    
    
    file->AddFile(fileName, "comment");
    /* 
    -----createFirstVersion()
    Use dialog to get comment to go with this initial version
    Invoke FileArchiver::insertNew()
    Invoke this->retrieveVersionDataForFile()
     
    */

}

void MyWindow::RetrieveVersionDataForFile()
{
    
    /* 

    ---RetrieveVersionDataForFile()
    Clear any existing data in table model used to display version database
    Invoke FileArchiver::getVersionInfo(filename) via FileArchiver object
    Repopulate table model with VersionInfoRecords displayed
    Adjust display*/
    
}

void MyWindow::RetrieveVersion()
{
    
    /*Retrieve version
   Use RetrievForm dialog to get details of where retrieved file to be placed
   Invoke FileArchiver::retrieveVersion(version-number, filename, retrieved name) via 
          FileArchiver object*/
    
    retrieveWindow = new RetrieveForm;
    
    retrieveWindow->show();

}



/*Selection of Entry in version table display
  Record in instance members details of the row selected and the actual version number that
      corresponds to the selected row*/


