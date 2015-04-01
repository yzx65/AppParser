/****************************************************************************
** Meta object code from reading C++ file 'selectemulatordlg.h'
**
** Created: Wed Apr 1 09:12:24 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "StdAfx.h"
#include "../../selectemulatordlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'selectemulatordlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SelectEmulatorDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      29,   24,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SelectEmulatorDlg[] = {
    "SelectEmulatorDlg\0\0OK()\0item\0"
    "OnLstEmulatorsItemDoubleClicked(QListWidgetItem*)\0"
};

void SelectEmulatorDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SelectEmulatorDlg *_t = static_cast<SelectEmulatorDlg *>(_o);
        switch (_id) {
        case 0: _t->OK(); break;
        case 1: _t->OnLstEmulatorsItemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SelectEmulatorDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SelectEmulatorDlg::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_SelectEmulatorDlg,
      qt_meta_data_SelectEmulatorDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SelectEmulatorDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SelectEmulatorDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SelectEmulatorDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SelectEmulatorDlg))
        return static_cast<void*>(const_cast< SelectEmulatorDlg*>(this));
    return QFrame::qt_metacast(_clname);
}

int SelectEmulatorDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void SelectEmulatorDlg::OK()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
