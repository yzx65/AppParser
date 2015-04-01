/****************************************************************************
** Meta object code from reading C++ file 'ios_emulatordlg.h'
**
** Created: Wed Apr 1 16:19:37 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "StdAfx.h"
#include "../../ios_emulatordlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ios_emulatordlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Emulator[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   10,    9,    9, 0x05,
      44,    9,    9,    9, 0x05,
      62,    9,    9,    9, 0x05,
      82,    9,    9,    9, 0x05,
     105,   99,    9,    9, 0x05,
     132,    9,    9,    9, 0x05,
     153,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
     176,    9,    9,    9, 0x0a,
     196,    9,    9,    9, 0x0a,
     217,    9,    9,    9, 0x0a,
     237,    9,    9,    9, 0x0a,
     262,  254,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Emulator[] = {
    "Emulator\0\0status\0ProcessTaskStatus(QString)\0"
    "ProcessTaskDone()\0ProcessTaskFailed()\0"
    "DeviceListDone()\0value\0"
    "RecoveryBackupProcess(int)\0"
    "RecoveryBackupDone()\0RecoveryBackupFailed()\0"
    "ProcessExportTask()\0ProcessInstallTask()\0"
    "RefreshDeviceList()\0RecoveryBackup()\0"
    "process\0DoNotify(int)\0"
};

void Emulator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Emulator *_t = static_cast<Emulator *>(_o);
        switch (_id) {
        case 0: _t->ProcessTaskStatus((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->ProcessTaskDone(); break;
        case 2: _t->ProcessTaskFailed(); break;
        case 3: _t->DeviceListDone(); break;
        case 4: _t->RecoveryBackupProcess((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->RecoveryBackupDone(); break;
        case 6: _t->RecoveryBackupFailed(); break;
        case 7: _t->ProcessExportTask(); break;
        case 8: _t->ProcessInstallTask(); break;
        case 9: _t->RefreshDeviceList(); break;
        case 10: _t->RecoveryBackup(); break;
        case 11: _t->DoNotify((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Emulator::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Emulator::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Emulator,
      qt_meta_data_Emulator, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Emulator::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Emulator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Emulator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Emulator))
        return static_cast<void*>(const_cast< Emulator*>(this));
    return QObject::qt_metacast(_clname);
}

int Emulator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void Emulator::ProcessTaskStatus(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Emulator::ProcessTaskDone()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void Emulator::ProcessTaskFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void Emulator::DeviceListDone()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void Emulator::RecoveryBackupProcess(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Emulator::RecoveryBackupDone()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void Emulator::RecoveryBackupFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}
static const uint qt_meta_data_IOS_EmulatorDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,
      37,   16,   16,   16, 0x05,
      58,   16,   16,   16, 0x05,
      78,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      95,   16,   16,   16, 0x0a,
     116,   16,   16,   16, 0x0a,
     140,   16,   16,   16, 0x0a,
     162,   16,   16,   16, 0x0a,
     194,  187,   16,   16, 0x0a,
     221,   16,   16,   16, 0x0a,
     239,   16,   16,   16, 0x0a,
     259,   16,   16,   16, 0x0a,
     283,   16,   16,   16, 0x0a,
     318,  312,   16,   16, 0x0a,
     345,   16,   16,   16, 0x0a,
     366,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_IOS_EmulatorDlg[] = {
    "IOS_EmulatorDlg\0\0ProcessExportTask()\0"
    "ProcessInstallTask()\0RefreshDeviceList()\0"
    "RecoveryBackup()\0OnBtnExportClicked()\0"
    "OnBtnExportAllClicked()\0OnBtnInstallClicked()\0"
    "OnBtnInstallAllClicked()\0status\0"
    "ProcessTaskStatus(QString)\0ProcessTaskDone()\0"
    "ProcessTaskFailed()\0RefreshDeviceListDone()\0"
    "OnBtnRecoveryBackupClicked()\0value\0"
    "RecoveryBackupProcess(int)\0"
    "RecoveryBackupDone()\0RecoveryBackupFailed()\0"
};

void IOS_EmulatorDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        IOS_EmulatorDlg *_t = static_cast<IOS_EmulatorDlg *>(_o);
        switch (_id) {
        case 0: _t->ProcessExportTask(); break;
        case 1: _t->ProcessInstallTask(); break;
        case 2: _t->RefreshDeviceList(); break;
        case 3: _t->RecoveryBackup(); break;
        case 4: _t->OnBtnExportClicked(); break;
        case 5: _t->OnBtnExportAllClicked(); break;
        case 6: _t->OnBtnInstallClicked(); break;
        case 7: _t->OnBtnInstallAllClicked(); break;
        case 8: _t->ProcessTaskStatus((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->ProcessTaskDone(); break;
        case 10: _t->ProcessTaskFailed(); break;
        case 11: _t->RefreshDeviceListDone(); break;
        case 12: _t->OnBtnRecoveryBackupClicked(); break;
        case 13: _t->RecoveryBackupProcess((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->RecoveryBackupDone(); break;
        case 15: _t->RecoveryBackupFailed(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData IOS_EmulatorDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject IOS_EmulatorDlg::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_IOS_EmulatorDlg,
      qt_meta_data_IOS_EmulatorDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &IOS_EmulatorDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *IOS_EmulatorDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *IOS_EmulatorDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IOS_EmulatorDlg))
        return static_cast<void*>(const_cast< IOS_EmulatorDlg*>(this));
    return QFrame::qt_metacast(_clname);
}

int IOS_EmulatorDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void IOS_EmulatorDlg::ProcessExportTask()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void IOS_EmulatorDlg::ProcessInstallTask()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void IOS_EmulatorDlg::RefreshDeviceList()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void IOS_EmulatorDlg::RecoveryBackup()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
