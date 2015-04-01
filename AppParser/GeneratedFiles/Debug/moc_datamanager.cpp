/****************************************************************************
** Meta object code from reading C++ file 'datamanager.h'
**
** Created: Wed Apr 1 13:49:49 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "StdAfx.h"
#include "../../datamanager.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'datamanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DataManager[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: signature, parameters, type, tag, flags
      21,   17,   13,   12, 0x02,
      56,   17,   13,   12, 0x02,
      92,   17,   13,   12, 0x02,
     122,   17,   13,   12, 0x02,
     155,   17,   13,   12, 0x02,
     189,   17,   13,   12, 0x02,
     226,   17,   13,   12, 0x02,
     259,   17,   13,   12, 0x02,
     295,   17,   13,   12, 0x02,
     328,   17,   13,   12, 0x02,
     357,   17,   13,   12, 0x02,
     390,   17,   13,   12, 0x02,
     421,   17,   13,   12, 0x02,
     458,   17,   13,   12, 0x02,
     499,   17,   13,   12, 0x02,
     535,   17,   13,   12, 0x02,
     571,   17,   13,   12, 0x02,
     610,   17,   13,   12, 0x02,
     651,   17,   13,   12, 0x02,
     691,   17,   13,   12, 0x02,
     724,   17,   13,   12, 0x02,
     759,   17,   13,   12, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_DataManager[] = {
    "DataManager\0\0int\0key\0"
    "GetKeyChainInfoCount(std::wstring)\0"
    "GetSystemAppInfoCount(std::wstring)\0"
    "GetSmsInfoCount(std::wstring)\0"
    "GetSmsInfoCountDel(std::wstring)\0"
    "GetContactInfoCount(std::wstring)\0"
    "GetContactInfoCountDel(std::wstring)\0"
    "GetRecordInfoCount(std::wstring)\0"
    "GetRecordInfoCountDel(std::wstring)\0"
    "GetSnsAppInfoCount(std::wstring)\0"
    "GetQQInfoCount(std::wstring)\0"
    "GetWeixinInfoCount(std::wstring)\0"
    "GetLineInfoCount(std::wstring)\0"
    "GetBrowserAppInfoCount(std::wstring)\0"
    "GetDefaultBrowserInfoCount(std::wstring)\0"
    "GetUCBrowserInfoCount(std::wstring)\0"
    "GetQQBrowserInfoCount(std::wstring)\0"
    "GetBaiduBrowserInfoCount(std::wstring)\0"
    "GetJinShanBrowserInfoCount(std::wstring)\0"
    "GetSafariBrowserInfoCount(std::wstring)\0"
    "GetMapAppInfoCount(std::wstring)\0"
    "GetBaiduMapInfoCount(std::wstring)\0"
    "GetGaodeMapInfoCount(std::wstring)\0"
};

void DataManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DataManager *_t = static_cast<DataManager *>(_o);
        switch (_id) {
        case 0: { int _r = _t->GetKeyChainInfoCount((*reinterpret_cast< std::wstring(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 1: { int _r = _t->GetSystemAppInfoCount((*reinterpret_cast< std::wstring(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 2: { int _r = _t->GetSmsInfoCount((*reinterpret_cast< std::wstring(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->GetSmsInfoCountDel((*reinterpret_cast< std::wstring(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { int _r = _t->GetContactInfoCount((*reinterpret_cast< std::wstring(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 5: { int _r = _t->GetContactInfoCountDel((*reinterpret_cast< std::wstring(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 6: { int _r = _t->GetRecordInfoCount((*reinterpret_cast< std::wstring(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 7: { int _r = _t->GetRecordInfoCountDel((*reinterpret_cast< std::wstring(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 8: { int _r = _t->GetSnsAppInfoCount((*reinterpret_cast< std::wstring(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 9: { int _r = _t->GetQQInfoCount((*reinterpret_cast< std::wstring(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 10: { int _r = _t->GetWeixinInfoCount((*reinterpret_cast< std::wstring(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 11: { int _r = _t->GetLineInfoCount((*reinterpret_cast< std::wstring(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 12: { int _r = _t->GetBrowserAppInfoCount((*reinterpret_cast< std::wstring(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 13: { int _r = _t->GetDefaultBrowserInfoCount((*reinterpret_cast< std::wstring(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 14: { int _r = _t->GetUCBrowserInfoCount((*reinterpret_cast< std::wstring(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 15: { int _r = _t->GetQQBrowserInfoCount((*reinterpret_cast< std::wstring(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 16: { int _r = _t->GetBaiduBrowserInfoCount((*reinterpret_cast< std::wstring(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 17: { int _r = _t->GetJinShanBrowserInfoCount((*reinterpret_cast< std::wstring(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 18: { int _r = _t->GetSafariBrowserInfoCount((*reinterpret_cast< std::wstring(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 19: { int _r = _t->GetMapAppInfoCount((*reinterpret_cast< std::wstring(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 20: { int _r = _t->GetBaiduMapInfoCount((*reinterpret_cast< std::wstring(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 21: { int _r = _t->GetGaodeMapInfoCount((*reinterpret_cast< std::wstring(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DataManager::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DataManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DataManager,
      qt_meta_data_DataManager, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DataManager::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DataManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DataManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DataManager))
        return static_cast<void*>(const_cast< DataManager*>(this));
    return QObject::qt_metacast(_clname);
}

int DataManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
