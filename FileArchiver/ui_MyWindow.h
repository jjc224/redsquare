/********************************************************************************
** Form generated from reading UI file 'MyWindow.ui'
**
<<<<<<< HEAD
** Created: Sun Sep 27 15:07:28 2015
=======
** Created: Wed Sep 30 03:50:09 2015
>>>>>>> a64dd150894d09314da530ad31cdb43f656cbdf5
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYWINDOW_H
#define UI_MYWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTableView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyWindow
{
public:
    QWidget *centralwidget;
    QLabel *labelFile;
    QPushButton *selectFileBttn;
    QLabel *labelVersionData;
    QTableView *tableView;
    QPushButton *saveCurrentBttn;
    QPushButton *retrieveVersionBttn;
    QPushButton *setReferenceBttn;
    QPushButton *showCommentBttn;
    QLineEdit *selectFilePath;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MyWindow)
    {
        if (MyWindow->objectName().isEmpty())
            MyWindow->setObjectName(QString::fromUtf8("MyWindow"));
        MyWindow->resize(765, 595);
        centralwidget = new QWidget(MyWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        labelFile = new QLabel(centralwidget);
        labelFile->setObjectName(QString::fromUtf8("labelFile"));
        labelFile->setGeometry(QRect(20, 10, 51, 51));
        selectFileBttn = new QPushButton(centralwidget);
        selectFileBttn->setObjectName(QString::fromUtf8("selectFileBttn"));
        selectFileBttn->setGeometry(QRect(640, 20, 98, 27));
        labelVersionData = new QLabel(centralwidget);
        labelVersionData->setObjectName(QString::fromUtf8("labelVersionData"));
        labelVersionData->setGeometry(QRect(30, 100, 114, 17));
        labelVersionData->setMinimumSize(QSize(0, 0));
        labelVersionData->setSizeIncrement(QSize(0, 0));
        labelVersionData->setLineWidth(1);
        labelVersionData->setTextFormat(Qt::AutoText);
        labelVersionData->setScaledContents(false);
        tableView = new QTableView(centralwidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(30, 130, 551, 391));
        saveCurrentBttn = new QPushButton(centralwidget);
        saveCurrentBttn->setObjectName(QString::fromUtf8("saveCurrentBttn"));
        saveCurrentBttn->setGeometry(QRect(590, 130, 151, 27));
        retrieveVersionBttn = new QPushButton(centralwidget);
        retrieveVersionBttn->setObjectName(QString::fromUtf8("retrieveVersionBttn"));
        retrieveVersionBttn->setGeometry(QRect(590, 170, 151, 27));
        setReferenceBttn = new QPushButton(centralwidget);
        setReferenceBttn->setObjectName(QString::fromUtf8("setReferenceBttn"));
        setReferenceBttn->setGeometry(QRect(590, 210, 151, 27));
        showCommentBttn = new QPushButton(centralwidget);
        showCommentBttn->setObjectName(QString::fromUtf8("showCommentBttn"));
        showCommentBttn->setGeometry(QRect(590, 250, 151, 27));
        selectFilePath = new QLineEdit(centralwidget);
        selectFilePath->setObjectName(QString::fromUtf8("selectFilePath"));
        selectFilePath->setEnabled(false);
        selectFilePath->setGeometry(QRect(50, 20, 581, 27));
        MyWindow->setCentralWidget(centralwidget);
        labelFile->raise();
        selectFilePath->raise();
        selectFilePath->raise();
        selectFileBttn->raise();
        labelVersionData->raise();
        tableView->raise();
        saveCurrentBttn->raise();
        retrieveVersionBttn->raise();
        setReferenceBttn->raise();
        showCommentBttn->raise();
        statusbar = new QStatusBar(MyWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MyWindow->setStatusBar(statusbar);

        retranslateUi(MyWindow);

        QMetaObject::connectSlotsByName(MyWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MyWindow)
    {
        MyWindow->setWindowTitle(QApplication::translate("MyWindow", "MyWindow", 0, QApplication::UnicodeUTF8));
        labelFile->setText(QApplication::translate("MyWindow", "File", 0, QApplication::UnicodeUTF8));
        selectFileBttn->setText(QApplication::translate("MyWindow", "Select File", 0, QApplication::UnicodeUTF8));
        labelVersionData->setText(QApplication::translate("MyWindow", "Version Data", 0, QApplication::UnicodeUTF8));
        saveCurrentBttn->setText(QApplication::translate("MyWindow", "Save Current", 0, QApplication::UnicodeUTF8));
        retrieveVersionBttn->setText(QApplication::translate("MyWindow", "Retrieve Version", 0, QApplication::UnicodeUTF8));
        setReferenceBttn->setText(QApplication::translate("MyWindow", "Set as reference", 0, QApplication::UnicodeUTF8));
        showCommentBttn->setText(QApplication::translate("MyWindow", "Show comment", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MyWindow: public Ui_MyWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYWINDOW_H
