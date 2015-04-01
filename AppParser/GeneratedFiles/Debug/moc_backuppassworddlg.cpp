/****************************************************************************
** Meta object code from reading C++ file 'backuppassworddlg.h'
**
** Created: Wed Apr 1 13:49:50 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "StdAfx.h"
#include "../../backuppassworddlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'backuppassworddlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BackupPasswordDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      29,   24,   18,   18, 0x0a,
      52,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_BackupPasswordDlg[] = {
    "BackupPasswordDlg\0\0OK()\0text\0"
    "OnTextChanged(QString)\0OnBtnOKClicked()\0"
};

void BackupPasswordDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BackupPasswordDlg *_t = static_cast<BackupPasswordDlg *>(_o);
        switch (_id) {
        case 0: _t->OK(); break;
        case 1: _t->OnTextChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->OnBtnOKClicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData BackupPasswordDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BackupPasswordDlg::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_BackupPasswordDlg,
      qt_meta_data_BackupPasswordDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BackupPasswordDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BackupPasswordDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BackupPasswordDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BackupPasswordDlg))
        return static_cast<void*>(const_cast< BackupPasswordDlg*>(this));
    return QFrame::qt_metacast(_clname);
}

int BackupPasswordDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void BackupPasswordDlg::OK()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
