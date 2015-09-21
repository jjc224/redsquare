/* 
 * File:   RetrieveForm.h
 * Author: io447
 *
 * Created on 21 September 2015, 4:45 PM
 */

#ifndef _RETRIEVEFORM_H
#define	_RETRIEVEFORM_H

#include "ui_RetrieveForm.h"

class RetrieveForm : public QDialog {
    Q_OBJECT
public:
    RetrieveForm();
    virtual ~RetrieveForm();
private:
    Ui::RetrieveForm widget;
};

#endif	/* _RETRIEVEFORM_H */
