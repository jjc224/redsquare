/****************************************************************************
** Meta object code from reading C++ file 'MyWindow.h'
**
** Created: Tue Sep 29 19:07:42 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MyWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      23,    9,    9,    9, 0x0a,
      37,    9,    9,    9, 0x0a,
      60,   51,    9,    9, 0x0a,
      92,    9,    9,    9, 0x0a,
     121,    9,    9,    9, 0x0a,
     139,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MyWindow[] = {
    "MyWindow\0\0SelectFile()\0SaveCurrent()\0"
    "ShowComment()\0fileName\0"
    "CreateFirstVersion(std::string)\0"
    "RetrieveVersionDataForFile()\0"
    "RetrieveVersion()\0SetReferenceVersion()\0"
};

void MyWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MyWindow *_t = static_cast<MyWindow *>(_o);
        switch (_id) {
        case 0: _t->SelectFile(); break;
        case 1: _t->SaveCurrent(); break;
        case 2: _t->ShowComment(); break;
        case 3: _t->CreateFirstVersion((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 4: _t->RetrieveVersionDataForFile(); break;
        case 5: _t->RetrieveVersion(); break;
        case 6: _t->SetReferenceVersion(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MyWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MyWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MyWindow,
      qt_meta_data_MyWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MyWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MyWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MyWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyWindow))
        return static_cast<void*>(const_cast< MyWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MyWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
