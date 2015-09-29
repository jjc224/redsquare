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

    connect(widget.buttonBoxComment, SIGNAL(accepted()), this, SLOT(SetComment()));
    connect(widget.buttonBoxComment, SIGNAL(rejected()), this, SLOT(reject()));

}

GetCommentForm::~GetCommentForm() {
}

void GetCommentForm::SetComment()
{

    comment = widget.textGetCommentForm->toPlainText();  
}

QString GetCommentForm::GetComment()
{
    return comment;
}
