/****************************************************************************
** Meta object code from reading C++ file 'appdlg.h'
**
** Created: Wed Apr 1 09:12:28 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "StdAfx.h"
#include "../../appdlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'appdlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SaveDataThread[] = {

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

static const char qt_meta_stringdata_SaveDataThread[] = {
    "SaveDataThread\0"
};

void SaveDataThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SaveDataThread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SaveDataThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_SaveDataThread,
      qt_meta_data_SaveDataThread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SaveDataThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SaveDataThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SaveDataThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SaveDataThread))
        return static_cast<void*>(const_cast< SaveDataThread*>(this));
    return QThread::qt_metacast(_clname);
}

int SaveDataThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_AppDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,    8,    7,    7, 0x05,
      39,    8,    7,    7, 0x05,
      58,    8,    7,    7, 0x05,
      94,   85,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
     115,    7,    7,    7, 0x0a,
     131,    7,    7,    7, 0x0a,
     142,    7,    7,    7, 0x0a,
     167,  161,    7,    7, 0x08,
     198,    7,    7,    7, 0x08,
     221,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AppDlg[] = {
    "AppDlg\0\0action\0AddMenuAction(QAction*)\0"
    "AddSubMenu(QMenu*)\0RemoveMenuAction(QAction*)\0"
    "subTitle\0SetSubTitle(QString)\0"
    "SelectDataDir()\0SaveData()\0"
    "SaveDataFinished()\0index\0"
    "OnListViewClicked(QModelIndex)\0"
    "CurrentDeviceChanged()\0"
    "OnBtnCollapseNavBarClicked()\0"
};

void AppDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AppDlg *_t = static_cast<AppDlg *>(_o);
        switch (_id) {
        case 0: _t->AddMenuAction((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 1: _t->AddSubMenu((*reinterpret_cast< QMenu*(*)>(_a[1]))); break;
        case 2: _t->RemoveMenuAction((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 3: _t->SetSubTitle((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->SelectDataDir(); break;
        case 5: _t->SaveData(); break;
        case 6: _t->SaveDataFinished(); break;
        case 7: _t->OnListViewClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 8: _t->CurrentDeviceChanged(); break;
        case 9: _t->OnBtnCollapseNavBarClicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AppDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AppDlg::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_AppDlg,
      qt_meta_data_AppDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AppDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AppDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AppDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AppDlg))
        return static_cast<void*>(const_cast< AppDlg*>(this));
    return QFrame::qt_metacast(_clname);
}

int AppDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void AppDlg::AddMenuAction(QAction * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AppDlg::AddSubMenu(QMenu * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AppDlg::RemoveMenuAction(QAction * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AppDlg::SetSubTitle(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
