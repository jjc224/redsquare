/****************************************************************************
** Meta object code from reading C++ file 'RetrieveForm.h'
**
** Created: Wed Sep 30 09:52:34 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "RetrieveForm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RetrieveForm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RetrieveForm[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      32,   13,   13,   13, 0x0a,
      54,   13,   46,   13, 0x0a,
      69,   13,   46,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_RetrieveForm[] = {
    "RetrieveForm\0\0SelectDirectory()\0"
    "SetFileName()\0QString\0GetDirectory()\0"
    "GetOutputFilename()\0"
};

void RetrieveForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RetrieveForm *_t = static_cast<RetrieveForm *>(_o);
        switch (_id) {
        case 0: _t->SelectDirectory(); break;
        case 1: _t->SetFileName(); break;
        case 2: { QString _r = _t->GetDirectory();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 3: { QString _r = _t->GetOutputFilename();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData RetrieveForm::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RetrieveForm::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_RetrieveForm,
      qt_meta_data_RetrieveForm, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RetrieveForm::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RetrieveForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RetrieveForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RetrieveForm))
        return static_cast<void*>(const_cast< RetrieveForm*>(this));
    return QDialog::qt_metacast(_clname);
}

int RetrieveForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
