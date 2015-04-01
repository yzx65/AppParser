/****************************************************************************
** Meta object code from reading C++ file 'selectdirdlg.h'
**
** Created: Wed Apr 1 09:09:21 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "StdAfx.h"
#include "../../selectdirdlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'selectdirdlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SelectDirDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      24,   19,   13,   13, 0x05,
      38,   13,   13,   13, 0x05,
      59,   53,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      80,   13,   13,   13, 0x0a,
      89,   13,   13,   13, 0x0a,
     111,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SelectDirDlg[] = {
    "SelectDirDlg\0\0OK()\0size\0Resize(QSize)\0"
    "CenterWindow()\0title\0SetSubTitle(QString)\0"
    "Browse()\0SelectForensicsType()\0"
    "SelectForensicsTypeFinished()\0"
};

void SelectDirDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SelectDirDlg *_t = static_cast<SelectDirDlg *>(_o);
        switch (_id) {
        case 0: _t->OK(); break;
        case 1: _t->Resize((*reinterpret_cast< QSize(*)>(_a[1]))); break;
        case 2: _t->CenterWindow(); break;
        case 3: _t->SetSubTitle((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->Browse(); break;
        case 5: _t->SelectForensicsType(); break;
        case 6: _t->SelectForensicsTypeFinished(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SelectDirDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SelectDirDlg::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_SelectDirDlg,
      qt_meta_data_SelectDirDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SelectDirDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SelectDirDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SelectDirDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SelectDirDlg))
        return static_cast<void*>(const_cast< SelectDirDlg*>(this));
    return QFrame::qt_metacast(_clname);
}

int SelectDirDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void SelectDirDlg::OK()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void SelectDirDlg::Resize(QSize _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SelectDirDlg::CenterWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void SelectDirDlg::SetSubTitle(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
