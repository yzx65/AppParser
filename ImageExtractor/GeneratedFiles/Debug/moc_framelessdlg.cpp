/****************************************************************************
** Meta object code from reading C++ file 'framelessdlg.h'
**
** Created: Wed Mar 11 16:00:02 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../framelessdlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'framelessdlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FramelessDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   14,   13,   13, 0x0a,
      45,   38,   13,   13, 0x0a,
      73,   66,   13,   13, 0x0a,
      97,   66,   13,   13, 0x0a,
     129,  124,   13,   13, 0x0a,
     157,  148,   13,   13, 0x0a,
     183,  178,   13,   13, 0x0a,
     197,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FramelessDlg[] = {
    "FramelessDlg\0\0title\0SetTitle(QString)\0"
    "enable\0SetCloseEnable(bool)\0action\0"
    "AddMenuAction(QAction*)\0"
    "RemoveMenuAction(QAction*)\0menu\0"
    "AddSubMenu(QMenu*)\0subTitle\0"
    "SetSubTitle(QString)\0size\0Resize(QSize)\0"
    "CenterWindow()\0"
};

void FramelessDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FramelessDlg *_t = static_cast<FramelessDlg *>(_o);
        switch (_id) {
        case 0: _t->SetTitle((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->SetCloseEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->AddMenuAction((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 3: _t->RemoveMenuAction((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 4: _t->AddSubMenu((*reinterpret_cast< QMenu*(*)>(_a[1]))); break;
        case 5: _t->SetSubTitle((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->Resize((*reinterpret_cast< QSize(*)>(_a[1]))); break;
        case 7: _t->CenterWindow(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FramelessDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FramelessDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FramelessDlg,
      qt_meta_data_FramelessDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FramelessDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FramelessDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FramelessDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FramelessDlg))
        return static_cast<void*>(const_cast< FramelessDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int FramelessDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
