/* 
 * File:   MyWindow.h
 * Author: io447
 *
 * Created on 21 September 2015, 12:36 PM
 */

#ifndef _MYWINDOW_H
#define	_MYWINDOW_H

#include "ui_MyWindow.h"
using namespace std;

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
    void SetReferenceVersion();
private:
    Ui::MyWindow widget;
};

#endif	/* _MYWINDOW_H */
