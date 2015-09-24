/* 
 * File:   GetCommentForm.h
 * Author: io447
 *
 * Created on 21 September 2015, 4:35 PM
 */

#ifndef _GETCOMMENTFORM_H
#define	_GETCOMMENTFORM_H

#include "ui_GetCommentForm.h"

class GetCommentForm : public QDialog {
    Q_OBJECT
public:
    GetCommentForm();
    virtual ~GetCommentForm();
private:
    Ui::GetCommentForm widget;
};

#endif	/* _GETCOMMENTFORM_H */
