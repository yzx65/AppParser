/****************************************************************************
** Meta object code from reading C++ file 'parsethread.h'
**
** Created: Wed Mar 11 15:56:04 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "StdAfx.h"
#include "../../parsethread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'parsethread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ParseThread[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   13,   12,   12, 0x05,
      49,   43,   12,   12, 0x05,
      69,   43,   12,   12, 0x05,
      87,   12,   12,   12, 0x05,
      99,   12,   12,   12, 0x05,
     113,   12,   12,   12, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_ParseThread[] = {
    "ParseThread\0\0status\0CurrentStatus(QString)\0"
    "value\0CurrentProcess(int)\0TotalProcess(int)\0"
    "ParseDone()\0ParseFailed()\0"
    "QueryIosBackupPassword()\0"
};

void ParseThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ParseThread *_t = static_cast<ParseThread *>(_o);
        switch (_id) {
        case 0: _t->CurrentStatus((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->CurrentProcess((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->TotalProcess((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->ParseDone(); break;
        case 4: _t->ParseFailed(); break;
        case 5: _t->QueryIosBackupPassword(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ParseThread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ParseThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_ParseThread,
      qt_meta_data_ParseThread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ParseThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ParseThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ParseThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ParseThread))
        return static_cast<void*>(const_cast< ParseThread*>(this));
    return QThread::qt_metacast(_clname);
}

int ParseThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ParseThread::CurrentStatus(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ParseThread::CurrentProcess(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ParseThread::TotalProcess(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ParseThread::ParseDone()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void ParseThread::ParseFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void ParseThread::QueryIosBackupPassword()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}
QT_END_MOC_NAMESPACE
