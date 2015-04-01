/****************************************************************************
** Meta object code from reading C++ file 'qqinfodlg.h'
**
** Created: Wed Apr 1 09:09:21 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "StdAfx.h"
#include "../../qqinfodlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qqinfodlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ChildrenFilter[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_ChildrenFilter[] = {
    "ChildrenFilter\0"
};

void ChildrenFilter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ChildrenFilter::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ChildrenFilter::staticMetaObject = {
    { &QSortFilterProxyModel::staticMetaObject, qt_meta_stringdata_ChildrenFilter,
      qt_meta_data_ChildrenFilter, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ChildrenFilter::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ChildrenFilter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ChildrenFilter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ChildrenFilter))
        return static_cast<void*>(const_cast< ChildrenFilter*>(this));
    return QSortFilterProxyModel::qt_metacast(_clname);
}

int ChildrenFilter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSortFilterProxyModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_QQInfoDlg[] = {

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
      11,   10,   10,   10, 0x0a,
      23,   10,   10,   10, 0x0a,
      34,   10,   10,   10, 0x0a,
      46,   10,   10,   10, 0x0a,
      61,   57,   10,   10, 0x0a,
      99,   93,   10,   10, 0x08,
     128,   93,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QQInfoDlg[] = {
    "QQInfoDlg\0\0FrontShow()\0BackShow()\0"
    "FrontHide()\0BackHide()\0key\0"
    "OnEdtFilterTextChanged(QString)\0index\0"
    "OnCurrentAccountChanged(int)\0"
    "OnTrQQAccountsClicked(QModelIndex)\0"
};

void QQInfoDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QQInfoDlg *_t = static_cast<QQInfoDlg *>(_o);
        switch (_id) {
        case 0: _t->FrontShow(); break;
        case 1: _t->BackShow(); break;
        case 2: _t->FrontHide(); break;
        case 3: _t->BackHide(); break;
        case 4: _t->OnEdtFilterTextChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->OnCurrentAccountChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->OnTrQQAccountsClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QQInfoDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QQInfoDlg::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_QQInfoDlg,
      qt_meta_data_QQInfoDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QQInfoDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QQInfoDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QQInfoDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QQInfoDlg))
        return static_cast<void*>(const_cast< QQInfoDlg*>(this));
    return QFrame::qt_metacast(_clname);
}

int QQInfoDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
