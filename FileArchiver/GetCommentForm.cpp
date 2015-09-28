/*
 * File:   GetCommentForm.cpp
 * Author: io447
 *
 * Created on 21 September 2015, 4:35 PM
 */
#include <QFileDialog>
#include <QApplication>
#include <iostream>
#include <string>

#include "GetCommentForm.h"

GetCommentForm::GetCommentForm() {
    widget.setupUi(this);
}

GetCommentForm::~GetCommentForm() {
}

void GetCommentForm::SetComment()
{
    QString comment = widget.textGetCommentForm->toPlainText();
    
}

void GetCommentForm::GetComment()
{
}
