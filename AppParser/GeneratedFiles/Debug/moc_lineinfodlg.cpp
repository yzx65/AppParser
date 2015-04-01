/****************************************************************************
** Meta object code from reading C++ file 'lineinfodlg.h'
**
** Created: Wed Apr 1 13:49:48 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "StdAfx.h"
#include "../../lineinfodlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lineinfodlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LineInfoDlg[] = {

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
      13,   12,   12,   12, 0x0a,
      25,   12,   12,   12, 0x0a,
      36,   12,   12,   12, 0x0a,
      48,   12,   12,   12, 0x0a,
      59,   12,   12,   12, 0x0a,
     100,   96,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_LineInfoDlg[] = {
    "LineInfoDlg\0\0FrontShow()\0BackShow()\0"
    "FrontHide()\0BackHide()\0"
    "OnLstLineFriendsClicked(QModelIndex)\0"
    "key\0OnEdtFilterTextChanged(QString)\0"
};

void LineInfoDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LineInfoDlg *_t = static_cast<LineInfoDlg *>(_o);
        switch (_id) {
        case 0: _t->FrontShow(); break;
        case 1: _t->BackShow(); break;
        case 2: _t->FrontHide(); break;
        case 3: _t->BackHide(); break;
        case 4: _t->OnLstLineFriendsClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 5: _t->OnEdtFilterTextChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData LineInfoDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LineInfoDlg::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_LineInfoDlg,
      qt_meta_data_LineInfoDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LineInfoDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LineInfoDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LineInfoDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LineInfoDlg))
        return static_cast<void*>(const_cast< LineInfoDlg*>(this));
    return QFrame::qt_metacast(_clname);
}

int LineInfoDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
