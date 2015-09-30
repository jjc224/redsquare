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
#include <QStandardItemModel>

#include "MyWindow.h"
#include "FileArchiver.h"
#include "FileRecord.h"

MyWindow::MyWindow() {
    widget.setupUi(this);
	
    widget.saveCurrentBttn->setEnabled(false);
    widget.retrieveVersionBttn->setEnabled(false);
    widget.setReferenceBttn->setEnabled(false);
    widget.showCommentBttn->setEnabled(false);
    
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

    if (dialog.exec() == QDialog::Rejected)
    {
        return;
    }

    fileNames = dialog.selectedFiles();
    
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
    if(!currentPath->Exists(stdFileName))
    {
        CreateFirstVersion(stdFileName);
    }    
    
    RetrieveVersionDataForFile();
}

void MyWindow::SaveCurrent()
{
    FileRecord fileRec(fileName.toStdString());
    
    if(fileRec.IsChanged())
    {
        AddNewVersion(fileName.toStdString());
        RetrieveVersionDataForFile();
    }
    else
    {
        QMessageBox msgBox;
        
        msgBox.setWindowTitle("No save required.");
        msgBox.setText("No modifications since last version. No save necessary.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
}

void MyWindow::ShowComment()
{
        QModelIndexList indexes = widget.tableView->selectionModel()->selectedRows();
        
        if(indexes.size() > 0)
        {
			//get version number of selected record
			QVariant data = indexes[0].data(0);
            //retrieve version
			
            VersionRecord selectedVersion(fileName.toStdString(), data.toInt());
			if(selectedVersion.IsValid())
			{

				QMessageBox msgBox(QMessageBox::Information, "Comment for selected version", QString(selectedVersion.GetComment().c_str()), QMessageBox::Ok, 0);
            
			   msgBox.exec();
			}
        }
}

void MyWindow::SetReferenceVersion()
{
        QModelIndexList indexes = widget.tableView->selectionModel()->selectedRows();
        
        if(indexes.size() > 0)
        {
            QMessageBox msgBox(QMessageBox::Question, "Set reference version", 
                    "Are you sure you want to purge these records?", QMessageBox::Yes | QMessageBox::No, 0);
            msgBox.setDefaultButton(QMessageBox::No);
            
            if(msgBox.exec() == QMessageBox::Yes)
            {
                FileRecord fileRec(fileName.toStdString());
                const QAbstractItemModel *myModel = indexes[0].model();
                
                for(int i = myModel->data(myModel->index(0, 0)).toInt(); i < myModel->data(myModel->index(indexes[0].row(), 0)).toInt(); ++i)
                {
                    fileRec.GetVersion(i).PurgeVersion();
                }
                
                // Repopulate the table.
                RetrieveVersionDataForFile();
            }
        }
}

void MyWindow::CreateFirstVersion(std::string fileName)
{
    getCommentWindow = new GetCommentForm();
    QString comm;

    if(getCommentWindow->exec() == QDialog::Rejected)
    {
        return;
    }
    
    comm = getCommentWindow->GetComment();

    std::string commentStd = comm.toStdString();
    FileRecord fileRec;
    
    fileRec.CreateFile(fileName, commentStd);
}

void MyWindow::AddNewVersion(std::string fileName)
{
    getCommentWindow = new GetCommentForm();
    QString comm;

    if(getCommentWindow->exec() == QDialog::Rejected)
    {

        return;
    }
    
    comm = getCommentWindow->GetComment();
    
    std::string commentStd = comm.toStdString();
    FileRecord fileRec(fileName);

    comm = getCommentWindow->GetComment();
    fileRec.AddNewVersion(fileName, commentStd);
}

void MyWindow::RetrieveVersionDataForFile()
{
    FileRecord fileRec(fileName.toStdString());
    
    if(fileRec.GetNumberOfVersions() == 0)
    {
        return;
    }
        
    QStandardItemModel *myModel = new QStandardItemModel(fileRec.GetNumberOfVersions(), 3, this);
    myModel->clear();
    
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
	
	widget.saveCurrentBttn->setEnabled(true);
    widget.retrieveVersionBttn->setEnabled(true);
    widget.showCommentBttn->setEnabled(true);
    widget.setReferenceBttn->setEnabled(true);
	
    widget.tableView->show();
}

void MyWindow::RetrieveVersion()
{
    QString directory;
    QString outFilename;
    
    QModelIndexList indexes = widget.tableView->selectionModel()->selectedRows();
    
    if(!(indexes.size() > 0))
    {
        QMessageBox msgBox(QMessageBox::Information, "Error", 
                    "Please select the version to be retrieved", QMessageBox::Ok, 0);
            
        msgBox.exec();
        return;
        
    }
    
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
	
	//retrieve version
        if(indexes.size() > 0)
        {
            VersionRecord selectedVersion(fileName.toStdString(), indexes[0].row() + 1);
            selectedVersion.GetFileData(fullOutputPath);
        }
}
