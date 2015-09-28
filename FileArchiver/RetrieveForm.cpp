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
    
    connect(widget.pushButtonDirectory, SIGNAL(clicked()), this, SLOT(SelectDirectory()));
    
    
        widget.buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

        connect(widget.buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
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

    //Display name of file as chosen by user
    QString dirName;
    if(!dirNames.isEmpty())
    {
        dirName = dirNames[0];
        widget.lineEditDirectory->setText(dirName);
    }
    
    //convert to std string
    std::string stdFileName;
    stdFileName = dirName.toStdString();


}
void RetrieveForm::GetFileName(){
    
    //QString filename = widget.lineEditFilename->toPlainText();

}