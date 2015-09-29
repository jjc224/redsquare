/********************************************************************************
** Form generated from reading UI file 'GetCommentForm.ui'
**
<<<<<<< HEAD
** Created: Wed Sep 30 08:15:04 2015
=======
<<<<<<< HEAD
** Created: Sun Sep 27 15:07:28 2015
=======
** Created: Wed Sep 30 03:50:09 2015
>>>>>>> a64dd150894d09314da530ad31cdb43f656cbdf5
>>>>>>> b7c48f1f5b2809ec7cc7542cc79d21dba625bb28
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GETCOMMENTFORM_H
#define UI_GETCOMMENTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_GetCommentForm
{
public:
    QDialogButtonBox *buttonBoxComment;
    QLabel *labelGetCommentForm;
    QTextEdit *textGetCommentForm;

    void setupUi(QDialog *GetCommentForm)
    {
        if (GetCommentForm->objectName().isEmpty())
            GetCommentForm->setObjectName(QString::fromUtf8("GetCommentForm"));
        GetCommentForm->resize(400, 300);
        buttonBoxComment = new QDialogButtonBox(GetCommentForm);
        buttonBoxComment->setObjectName(QString::fromUtf8("buttonBoxComment"));
        buttonBoxComment->setGeometry(QRect(30, 240, 341, 32));
        buttonBoxComment->setOrientation(Qt::Horizontal);
        buttonBoxComment->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        labelGetCommentForm = new QLabel(GetCommentForm);
        labelGetCommentForm->setObjectName(QString::fromUtf8("labelGetCommentForm"));
        labelGetCommentForm->setGeometry(QRect(20, 20, 371, 17));
        textGetCommentForm = new QTextEdit(GetCommentForm);
        textGetCommentForm->setObjectName(QString::fromUtf8("textGetCommentForm"));
        textGetCommentForm->setGeometry(QRect(20, 50, 361, 171));

        retranslateUi(GetCommentForm);
        QObject::connect(buttonBoxComment, SIGNAL(accepted()), GetCommentForm, SLOT(accept()));
        QObject::connect(buttonBoxComment, SIGNAL(rejected()), GetCommentForm, SLOT(reject()));

        QMetaObject::connectSlotsByName(GetCommentForm);
    } // setupUi

    void retranslateUi(QDialog *GetCommentForm)
    {
        GetCommentForm->setWindowTitle(QApplication::translate("GetCommentForm", "GetCommentForm", 0, QApplication::UnicodeUTF8));
        labelGetCommentForm->setText(QApplication::translate("GetCommentForm", "Comment to go with version file:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GetCommentForm: public Ui_GetCommentForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GETCOMMENTFORM_H
