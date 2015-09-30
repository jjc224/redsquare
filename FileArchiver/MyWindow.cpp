/*
 * File:   MyWindow.cpp
 * Author: io447
 *
 * Created on 21 September 2015, 12:36 PM
 */
#include <QFileDialog>
#include <QApplication>
#include <QMessageBox>
#include <iostream>
#include <string>
#include <QDebug>
#include <boost/lexical_cast.hpp>

#include "MyWindow.h"
#include "FileArchiver.h"
#include "FileRecord.h"
#include "TableModel.h"

MyWindow::MyWindow() {
    widget.setupUi(this);
	
	//widget.saveCurrentBttn->setEnabled(false);
	//widget.retrieveVersionBttn->setEnabled(false);
	//widget.setReferenceBttn->setEnabled(false);
	//widget.showCommentBttn->setEnabled(false);
    
    //connect SelectFile() with selectFileBttn
    connect(widget.selectFileBttn, SIGNAL(clicked()), this, SLOT(SelectFile()));
	//connect saveCurrentBttn with SaveCurrent()
	connect(widget.saveCurrentBttn, SIGNAL(clicked()), this, SLOT(SaveCurrent()));
	//connect RetrieveVersion() with retrieveVersionBttn which will open RetrieveForm
    connect(widget.retrieveVersionBttn, SIGNAL(clicked()), this, SLOT(RetrieveVersion()));

	//connect setReferenceBttn with SetReferenceVersion() to delete unnecessary file versions
	connect(widget.setReferenceBttn, SIGNAL(clicked()), this, SLOT(SetReferenceVersion()));
	//connect ShowComment() with showCommentBttn
	connect(widget.showCommentBttn, SIGNAL(clicked()), this, SLOT(ShowComment()));

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
    if(!fileNames.isEmpty())
    {
        fileName = fileNames[0];
        widget.selectFilePath->setText(fileName);
    }
    
    //convert to std string
    std::string stdFileName;
    stdFileName = fileName.toStdString();
    
    //for now not catching exception bad_alloc
    FilePtr currentPath = new FileArchiver;
    
    //If a record already exists
    if(currentPath->Exists(stdFileName))
    {
        //Invoke this->retrieveVersionDataForFile() to get collection of VersionInfoRecords 
        //and enable Save
    }    
    else
    {
       // Invoke this->createFirstVersion() to create initial version of file in persistent storage
        CreateFirstVersion(stdFileName);
    }
    
    RetrieveVersionDataForFile();
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
        QModelIndexList indexes = widget.tableView->selectionModel()->selectedRows();
        
        if(indexes.size() > 0)
        {
            //retrieve version
            VersionRecord selectedVersion(fileName.toStdString(), indexes[0].row() + 1);
            QMessageBox msgBox;
        
            msgBox.setWindowTitle("Comment for selected version");
            msgBox.setText(QString(selectedVersion.GetComment().c_str()));
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.exec();
        }
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
    QString comm;

    if(getCommentWindow->exec() == QDialog::Accepted)
    {
        comm = getCommentWindow->GetComment();
    }

    std::string commentStd = comm.toStdString();
    //Invoke FileArchiver::insertNew()
    //create new record --> catch bad_alloc
    //FilePtr file = new FileArchiver;
    FileRecord fileRec;
    fileRec.CreateFile(fileName, commentStd);
    
   //invoke this->retrieveVersionDataForFile()
    

}

void MyWindow::RetrieveVersionDataForFile()
{
    FileRecord fileRec(fileName.toStdString());
    QStandardItemModel *myModel = new QStandardItemModel(fileRec.GetNumberOfVersions(), 3, this);
    
    myModel->setHorizontalHeaderItem(0, new QStandardItem(QString("Version #")));
    myModel->setHorizontalHeaderItem(1, new QStandardItem(QString("Date")));
    myModel->setHorizontalHeaderItem(2, new QStandardItem(QString("Size")));
    
    vector<VersionRecord> versionRecs = fileRec.GetAllVersions();
    unsigned int currentRow = 0;
    
    for(vector<VersionRecord>::iterator it = versionRecs.begin(); it != versionRecs.end(); ++it)
    {
        myModel->setItem(currentRow, 0, new QStandardItem(QString(boost::lexical_cast<string>(it->GetVersionNumber()).c_str())));
        myModel->setItem(currentRow, 1, new QStandardItem(QString(it->GetFormattedModificationTime().c_str())));
        myModel->setItem(currentRow, 2, new QStandardItem(QString(boost::lexical_cast<string>(it->GetSize()).c_str())));
    
        ++currentRow;
    }
    
    widget.tableView->setModel(myModel);
    widget.tableView->resizeColumnsToContents();
    widget.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    widget.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    widget.tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    widget.tableView->show();
}

void MyWindow::RetrieveVersion()
{
	//get current version by selected item from tableview
		//need code here
	
    QString directory;
    QString outFilename;
    
    retrieveWindow = new RetrieveForm;
	//execute RetrieveForm and details of where retrieved file will be placed
    
    if(retrieveWindow->exec() == QDialog::Accepted)
    {
        directory = retrieveWindow->GetDirectory();
        outFilename = retrieveWindow->GetOutputFilename();
    }
	
	//convert data from RetrieveForm to full file output path
	std::string fullOutputPath;
	
	fullOutputPath += directory.toStdString();
	fullOutputPath += "/";
	fullOutputPath += outFilename.toStdString();
	
        QModelIndexList indexes = widget.tableView->selectionModel()->selectedRows();
        
	//retrieve version
	VersionRecord selectedVersion(fileName.toStdString(), indexes[0].row() + 1);
	selectedVersion.GetFileData(fullOutputPath);
}



/*Selection of Entry in version table display
  Record in instance members details of the row selected and the actual version number that
      corresponds to the selected row*/


