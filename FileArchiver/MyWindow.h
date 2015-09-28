/* 
 * File:   MyWindow.h
 * Author: io447
 *
 * Created on 21 September 2015, 12:36 PM
 */

#ifndef _MYWINDOW_H
#define	_MYWINDOW_H

#include "ui_MyWindow.h"
#include "GetCommentForm.h"
#include "RetrieveForm.h"
using namespace std;


class FileArchiver;
class FileRecord;
typedef FileArchiver* FilePtr;
class TableModel;


class MyWindow : public QMainWindow {
    Q_OBJECT
public:
    MyWindow();
    virtual ~MyWindow();
public slots:
    //select file
    void SelectFile();
    void SaveCurrent();
    void ShowComment();
    void CreateFirstVersion(std::string fileName);
    void RetrieveVersionDataForFile();
    void RetrieveVersion();
    void SetReferenceVersion();
private:
    Ui::MyWindow widget;
    GetCommentForm * getCommentWindow;
    RetrieveForm * retrieveWindow;
    TableModel * tablemodel;
};

#endif	/* _MYWINDOW_H */
