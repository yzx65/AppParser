/****************************************************************************
** Meta object code from reading C++ file 'weixininfodlg.h'
**
** Created: Wed Apr 1 13:49:46 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "StdAfx.h"
#include "../../weixininfodlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'weixininfodlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WeixinInfoDlg[] = {

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
      15,   14,   14,   14, 0x0a,
      27,   14,   14,   14, 0x0a,
      38,   14,   14,   14, 0x0a,
      50,   14,   14,   14, 0x0a,
      65,   61,   14,   14, 0x0a,
     103,   97,   14,   14, 0x08,
     132,   97,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_WeixinInfoDlg[] = {
    "WeixinInfoDlg\0\0FrontShow()\0BackShow()\0"
    "FrontHide()\0BackHide()\0key\0"
    "OnEdtFilterTextChanged(QString)\0index\0"
    "OnCurrentAccountChanged(int)\0"
    "OnLstWeixinFriendsClicked(QModelIndex)\0"
};

void WeixinInfoDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WeixinInfoDlg *_t = static_cast<WeixinInfoDlg *>(_o);
        switch (_id) {
        case 0: _t->FrontShow(); break;
        case 1: _t->BackShow(); break;
        case 2: _t->FrontHide(); break;
        case 3: _t->BackHide(); break;
        case 4: _t->OnEdtFilterTextChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->OnCurrentAccountChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->OnLstWeixinFriendsClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WeixinInfoDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WeixinInfoDlg::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_WeixinInfoDlg,
      qt_meta_data_WeixinInfoDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WeixinInfoDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WeixinInfoDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WeixinInfoDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WeixinInfoDlg))
        return static_cast<void*>(const_cast< WeixinInfoDlg*>(this));
    return QFrame::qt_metacast(_clname);
}

int WeixinInfoDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
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
