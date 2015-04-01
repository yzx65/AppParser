/****************************************************************************
** Meta object code from reading C++ file 'parsedlg.h'
**
** Created: Wed Mar 11 15:56:04 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "StdAfx.h"
#include "../../parsedlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'parsedlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ParseDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      15,    9,    9,    9, 0x0a,
      28,    9,    9,    9, 0x0a,
      40,    9,    9,    9, 0x0a,
      61,   54,    9,    9, 0x0a,
      90,   84,    9,    9, 0x0a,
     110,   84,    9,    9, 0x0a,
     128,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ParseDlg[] = {
    "ParseDlg\0\0OK()\0StartParse()\0ParseDone()\0"
    "ParseFailed()\0status\0CurrentStatus(QString)\0"
    "value\0CurrentProcess(int)\0TotalProcess(int)\0"
    "OnQueryIosBackupPassword()\0"
};

void ParseDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ParseDlg *_t = static_cast<ParseDlg *>(_o);
        switch (_id) {
        case 0: _t->OK(); break;
        case 1: _t->StartParse(); break;
        case 2: _t->ParseDone(); break;
        case 3: _t->ParseFailed(); break;
        case 4: _t->CurrentStatus((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->CurrentProcess((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->TotalProcess((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->OnQueryIosBackupPassword(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ParseDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ParseDlg::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_ParseDlg,
      qt_meta_data_ParseDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ParseDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ParseDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ParseDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ParseDlg))
        return static_cast<void*>(const_cast< ParseDlg*>(this));
    return QFrame::qt_metacast(_clname);
}

int ParseDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ParseDlg::OK()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
