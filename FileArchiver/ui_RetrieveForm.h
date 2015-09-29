/********************************************************************************
** Form generated from reading UI file 'RetrieveForm.ui'
**
** Created: Sun Sep 27 15:07:28 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RETRIEVEFORM_H
#define UI_RETRIEVEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_RetrieveForm
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *labelDirectory;
    QLineEdit *lineEditDirectory;
    QPushButton *pushButtonDirectory;
    QLabel *labelFilename;
    QLineEdit *lineEditFilename;

    void setupUi(QDialog *RetrieveForm)
    {
        if (RetrieveForm->objectName().isEmpty())
            RetrieveForm->setObjectName(QString::fromUtf8("RetrieveForm"));
        RetrieveForm->resize(582, 190);
        buttonBox = new QDialogButtonBox(RetrieveForm);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(220, 140, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        labelDirectory = new QLabel(RetrieveForm);
        labelDirectory->setObjectName(QString::fromUtf8("labelDirectory"));
        labelDirectory->setGeometry(QRect(20, 20, 81, 31));
        lineEditDirectory = new QLineEdit(RetrieveForm);
        lineEditDirectory->setObjectName(QString::fromUtf8("lineEditDirectory"));
        lineEditDirectory->setGeometry(QRect(90, 20, 331, 27));
        pushButtonDirectory = new QPushButton(RetrieveForm);
        pushButtonDirectory->setObjectName(QString::fromUtf8("pushButtonDirectory"));
        pushButtonDirectory->setGeometry(QRect(440, 20, 121, 27));
        labelFilename = new QLabel(RetrieveForm);
        labelFilename->setObjectName(QString::fromUtf8("labelFilename"));
        labelFilename->setGeometry(QRect(20, 70, 71, 31));
        lineEditFilename = new QLineEdit(RetrieveForm);
        lineEditFilename->setObjectName(QString::fromUtf8("lineEditFilename"));
        lineEditFilename->setGeometry(QRect(90, 70, 181, 27));

        retranslateUi(RetrieveForm);
        QObject::connect(buttonBox, SIGNAL(accepted()), RetrieveForm, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), RetrieveForm, SLOT(reject()));

        QMetaObject::connectSlotsByName(RetrieveForm);
    } // setupUi

    void retranslateUi(QDialog *RetrieveForm)
    {
        RetrieveForm->setWindowTitle(QApplication::translate("RetrieveForm", "RetrieveForm", 0, QApplication::UnicodeUTF8));
        labelDirectory->setText(QApplication::translate("RetrieveForm", "Directory", 0, QApplication::UnicodeUTF8));
        pushButtonDirectory->setText(QApplication::translate("RetrieveForm", "Select Directory", 0, QApplication::UnicodeUTF8));
        labelFilename->setText(QApplication::translate("RetrieveForm", "Filename", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RetrieveForm: public Ui_RetrieveForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RETRIEVEFORM_H
