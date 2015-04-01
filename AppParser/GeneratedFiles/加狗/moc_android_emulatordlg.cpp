/****************************************************************************
** Meta object code from reading C++ file 'android_emulatordlg.h'
**
** Created: Wed Mar 11 15:56:01 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "StdAfx.h"
#include "../../android_emulatordlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'android_emulatordlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ExportWorker[] = {

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
      21,   14,   13,   13, 0x05,
      48,   13,   13,   13, 0x05,
      66,   13,   13,   13, 0x05,
      86,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
     102,   13,   13,   13, 0x0a,
     122,   13,   13,   13, 0x0a,
     145,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ExportWorker[] = {
    "ExportWorker\0\0status\0ProcessTaskStatus(QString)\0"
    "ProcessTaskDone()\0ProcessTaskFailed()\0"
    "EmulatorReady()\0ProcessExportTask()\0"
    "ProcessUninstallTask()\0CheckEmulatorReady()\0"
};

void ExportWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ExportWorker *_t = static_cast<ExportWorker *>(_o);
        switch (_id) {
        case 0: _t->ProcessTaskStatus((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->ProcessTaskDone(); break;
        case 2: _t->ProcessTaskFailed(); break;
        case 3: _t->EmulatorReady(); break;
        case 4: _t->ProcessExportTask(); break;
        case 5: _t->ProcessUninstallTask(); break;
        case 6: _t->CheckEmulatorReady(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ExportWorker::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ExportWorker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ExportWorker,
      qt_meta_data_ExportWorker, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ExportWorker::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ExportWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ExportWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ExportWorker))
        return static_cast<void*>(const_cast< ExportWorker*>(this));
    return QObject::qt_metacast(_clname);
}

int ExportWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void ExportWorker::ProcessTaskStatus(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ExportWorker::ProcessTaskDone()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void ExportWorker::ProcessTaskFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void ExportWorker::EmulatorReady()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
static const uint qt_meta_data_Android_EmulatorDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x05,
      42,   20,   20,   20, 0x05,
      62,   20,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
      85,   20,   20,   20, 0x0a,
     106,   20,   20,   20, 0x0a,
     130,   20,   20,   20, 0x0a,
     154,   20,   20,   20, 0x0a,
     181,   20,   20,   20, 0x0a,
     204,   20,   20,   20, 0x0a,
     232,   20,   20,   20, 0x0a,
     251,   20,   20,   20, 0x0a,
     270,   20,   20,   20, 0x0a,
     291,   20,   20,   20, 0x0a,
     314,  307,   20,   20, 0x0a,
     341,   20,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Android_EmulatorDlg[] = {
    "Android_EmulatorDlg\0\0CheckEmulatorReady()\0"
    "ProcessExportTask()\0ProcessUninstallTask()\0"
    "OnBtnExportClicked()\0OnBtnExportAllClicked()\0"
    "OnBtnUninstallClicked()\0"
    "OnBtnUninstallAllClicked()\0"
    "OnBtnEmulatorClicked()\0"
    "OnBtnToggleNetworkClicked()\0"
    "EmulatorFinished()\0EmulatorAttached()\0"
    "GenymotionFinished()\0EmulatorReady()\0"
    "status\0ProcessTaskStatus(QString)\0"
    "ProcessTaskDone()\0"
};

void Android_EmulatorDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Android_EmulatorDlg *_t = static_cast<Android_EmulatorDlg *>(_o);
        switch (_id) {
        case 0: _t->CheckEmulatorReady(); break;
        case 1: _t->ProcessExportTask(); break;
        case 2: _t->ProcessUninstallTask(); break;
        case 3: _t->OnBtnExportClicked(); break;
        case 4: _t->OnBtnExportAllClicked(); break;
        case 5: _t->OnBtnUninstallClicked(); break;
        case 6: _t->OnBtnUninstallAllClicked(); break;
        case 7: _t->OnBtnEmulatorClicked(); break;
        case 8: _t->OnBtnToggleNetworkClicked(); break;
        case 9: _t->EmulatorFinished(); break;
        case 10: _t->EmulatorAttached(); break;
        case 11: _t->GenymotionFinished(); break;
        case 12: _t->EmulatorReady(); break;
        case 13: _t->ProcessTaskStatus((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: _t->ProcessTaskDone(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Android_EmulatorDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Android_EmulatorDlg::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_Android_EmulatorDlg,
      qt_meta_data_Android_EmulatorDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Android_EmulatorDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Android_EmulatorDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Android_EmulatorDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Android_EmulatorDlg))
        return static_cast<void*>(const_cast< Android_EmulatorDlg*>(this));
    return QFrame::qt_metacast(_clname);
}

int Android_EmulatorDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void Android_EmulatorDlg::CheckEmulatorReady()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Android_EmulatorDlg::ProcessExportTask()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void Android_EmulatorDlg::ProcessUninstallTask()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
