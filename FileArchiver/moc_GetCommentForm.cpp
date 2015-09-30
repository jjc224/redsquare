/****************************************************************************
** Meta object code from reading C++ file 'GetCommentForm.h'
**
** Created: Thu Oct 1 03:44:50 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "GetCommentForm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GetCommentForm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GetCommentForm[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x0a,
      37,   15,   29,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GetCommentForm[] = {
    "GetCommentForm\0\0SetComment()\0QString\0"
    "GetComment()\0"
};

void GetCommentForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GetCommentForm *_t = static_cast<GetCommentForm *>(_o);
        switch (_id) {
        case 0: _t->SetComment(); break;
        case 1: { QString _r = _t->GetComment();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GetCommentForm::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GetCommentForm::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_GetCommentForm,
      qt_meta_data_GetCommentForm, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GetCommentForm::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GetCommentForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GetCommentForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GetCommentForm))
        return static_cast<void*>(const_cast< GetCommentForm*>(this));
    return QDialog::qt_metacast(_clname);
}

int GetCommentForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
