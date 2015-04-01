/****************************************************************************
** Meta object code from reading C++ file 'browserinfodlg.h'
**
** Created: Wed Apr 1 16:19:39 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "StdAfx.h"
#include "../../browserinfodlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'browserinfodlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BrowserInfoDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x0a,
      40,   15,   15,   15, 0x0a,
      81,   77,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_BrowserInfoDlg[] = {
    "BrowserInfoDlg\0\0CurrentDisplayChanged()\0"
    "OnLstBrowserDataClicked(QModelIndex)\0"
    "key\0OnEdtFilterTextChanged(QString)\0"
};

void BrowserInfoDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BrowserInfoDlg *_t = static_cast<BrowserInfoDlg *>(_o);
        switch (_id) {
        case 0: _t->CurrentDisplayChanged(); break;
        case 1: _t->OnLstBrowserDataClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 2: _t->OnEdtFilterTextChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData BrowserInfoDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BrowserInfoDlg::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_BrowserInfoDlg,
      qt_meta_data_BrowserInfoDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BrowserInfoDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BrowserInfoDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BrowserInfoDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BrowserInfoDlg))
        return static_cast<void*>(const_cast< BrowserInfoDlg*>(this));
    return QFrame::qt_metacast(_clname);
}

int BrowserInfoDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
