/****************************************************************************
** Meta object code from reading C++ file 'browserrecord.h'
**
** Created: Wed Apr 1 16:19:39 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "StdAfx.h"
#include "../../browserrecord.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'browserrecord.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BrowserRecord[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   15,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_BrowserRecord[] = {
    "BrowserRecord\0\0url\0OnLinkClicked(QUrl)\0"
};

void BrowserRecord::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BrowserRecord *_t = static_cast<BrowserRecord *>(_o);
        switch (_id) {
        case 0: _t->OnLinkClicked((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData BrowserRecord::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BrowserRecord::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_BrowserRecord,
      qt_meta_data_BrowserRecord, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BrowserRecord::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BrowserRecord::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BrowserRecord::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BrowserRecord))
        return static_cast<void*>(const_cast< BrowserRecord*>(this));
    return QFrame::qt_metacast(_clname);
}

int BrowserRecord::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
