/****************************************************************************
** Meta object code from reading C++ file 'smsinfodlg.h'
**
** Created: Wed Apr 1 16:19:36 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "StdAfx.h"
#include "../../smsinfodlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'smsinfodlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SmsInfoDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      24,   11,   11,   11, 0x0a,
      35,   11,   11,   11, 0x0a,
      47,   11,   11,   11, 0x0a,
      58,   11,   11,   11, 0x0a,
      98,   94,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SmsInfoDlg[] = {
    "SmsInfoDlg\0\0FrontShow()\0BackShow()\0"
    "FrontHide()\0BackHide()\0"
    "OnLstSmsFriendsClicked(QModelIndex)\0"
    "key\0OnEdtFilterTextChanged(QString)\0"
};

void SmsInfoDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SmsInfoDlg *_t = static_cast<SmsInfoDlg *>(_o);
        switch (_id) {
        case 0: _t->FrontShow(); break;
        case 1: _t->BackShow(); break;
        case 2: _t->FrontHide(); break;
        case 3: _t->BackHide(); break;
        case 4: _t->OnLstSmsFriendsClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 5: _t->OnEdtFilterTextChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SmsInfoDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SmsInfoDlg::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_SmsInfoDlg,
      qt_meta_data_SmsInfoDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SmsInfoDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SmsInfoDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SmsInfoDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SmsInfoDlg))
        return static_cast<void*>(const_cast< SmsInfoDlg*>(this));
    return QFrame::qt_metacast(_clname);
}

int SmsInfoDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
