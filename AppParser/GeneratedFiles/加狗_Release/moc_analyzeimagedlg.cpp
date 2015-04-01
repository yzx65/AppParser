/****************************************************************************
** Meta object code from reading C++ file 'analyzeimagedlg.h'
**
** Created: Wed Apr 1 09:12:29 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "StdAfx.h"
#include "../../analyzeimagedlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'analyzeimagedlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SearchImageThread[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      25,   19,   18,   18, 0x05,
      44,   19,   18,   18, 0x05,
      79,   65,   18,   18, 0x05,
     109,   18,   18,   18, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_SearchImageThread[] = {
    "SearchImageThread\0\0value\0TotalProgress(int)\0"
    "CurrentProgress(int)\0result,offset\0"
    "SearchResult(QString,__int64)\0"
    "SearchFinished()\0"
};

void SearchImageThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SearchImageThread *_t = static_cast<SearchImageThread *>(_o);
        switch (_id) {
        case 0: _t->TotalProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->CurrentProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->SearchResult((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< __int64(*)>(_a[2]))); break;
        case 3: _t->SearchFinished(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SearchImageThread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SearchImageThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_SearchImageThread,
      qt_meta_data_SearchImageThread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SearchImageThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SearchImageThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SearchImageThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SearchImageThread))
        return static_cast<void*>(const_cast< SearchImageThread*>(this));
    return QThread::qt_metacast(_clname);
}

int SearchImageThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void SearchImageThread::TotalProgress(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SearchImageThread::CurrentProgress(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SearchImageThread::SearchResult(QString _t1, __int64 _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SearchImageThread::SearchFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
static const uint qt_meta_data_AnalyzeImageDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      25,   17,   16,   16, 0x0a,
      44,   17,   16,   16, 0x0a,
      65,   16,   16,   16, 0x0a,
      96,   82,   16,   16, 0x0a,
     126,   16,   16,   16, 0x08,
     155,   16,   16,   16, 0x08,
     183,  178,   16,   16, 0x08,
     218,   16,   16,   16, 0x08,
     239,   16,   16,   16, 0x08,
     260,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AnalyzeImageDlg[] = {
    "AnalyzeImageDlg\0\0process\0TotalProgress(int)\0"
    "CurrentProgress(int)\0SearchFinished()\0"
    "result,offset\0SearchResult(QString,__int64)\0"
    "OnBtnBrowseSavePathClicked()\0"
    "OnBtnRecoveryClicked()\0text\0"
    "OnEdtSearchStrTextChanged(QString)\0"
    "OnBtnSearchClicked()\0OnBtnExportClicked()\0"
    "OnBtnBrowseImageClicked()\0"
};

void AnalyzeImageDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AnalyzeImageDlg *_t = static_cast<AnalyzeImageDlg *>(_o);
        switch (_id) {
        case 0: _t->TotalProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->CurrentProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->SearchFinished(); break;
        case 3: _t->SearchResult((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< __int64(*)>(_a[2]))); break;
        case 4: _t->OnBtnBrowseSavePathClicked(); break;
        case 5: _t->OnBtnRecoveryClicked(); break;
        case 6: _t->OnEdtSearchStrTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->OnBtnSearchClicked(); break;
        case 8: _t->OnBtnExportClicked(); break;
        case 9: _t->OnBtnBrowseImageClicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AnalyzeImageDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AnalyzeImageDlg::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_AnalyzeImageDlg,
      qt_meta_data_AnalyzeImageDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AnalyzeImageDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AnalyzeImageDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AnalyzeImageDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AnalyzeImageDlg))
        return static_cast<void*>(const_cast< AnalyzeImageDlg*>(this));
    return QFrame::qt_metacast(_clname);
}

int AnalyzeImageDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
