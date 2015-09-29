/*
 * File:   RetrieveForm.cpp
 * Author: io447
 *
 * Created on 21 September 2015, 4:45 PM
 */

#include <QFileDialog>
#include <QApplication>
#include <iostream>
#include <string>

#include "RetrieveForm.h"

RetrieveForm::RetrieveForm() {
    widget.setupUi(this);
    
	//select directory button
    connect(widget.pushButtonDirectory, SIGNAL(clicked()), this, SLOT(SelectDirectory()));
   //ok | cancel buttons
    connect(widget.buttonBox, SIGNAL(accepted()), this, SLOT(SetFileName()));
    connect(widget.buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

RetrieveForm::~RetrieveForm() {
}

void RetrieveForm::SelectDirectory()
{
    //declare new select file dialog
    QFileDialog dialogDir(this);
    //set mode to existing file
    dialogDir.setFileMode(QFileDialog::Directory);
    //set view mode to detail
    dialogDir.setViewMode(QFileDialog::Detail);
    
    QStringList dirNames;
    //QString fileName;
    if (dialogDir.exec())
    {
        //dialog.selectFile(fileName);
         dirNames = dialogDir.selectedFiles();
    }

    //Display name of directory as chosen by user
    QString dirName;
    if(!dirNames.isEmpty())
    {
        dirName = dirNames[0];
        widget.lineEditDirectory->setText(dirName);
    }
    
	directoryPath = dirName;

}
void RetrieveForm::SetFileName(){
    
    outputFilename = widget.lineEditFilename->text();

}

QString RetrieveForm::GetDirectory()
{
	return directoryPath;
}

QString RetrieveForm::GetOutputFilename()
{
	return outputFilename;
}