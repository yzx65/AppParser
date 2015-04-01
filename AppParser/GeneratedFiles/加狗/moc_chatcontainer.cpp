/****************************************************************************
** Meta object code from reading C++ file 'chatcontainer.h'
**
** Created: Wed Mar 11 15:56:02 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "StdAfx.h"
#include "../../chatcontainer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chatcontainer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ChatContainer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      26,   14,   14,   14, 0x05,
      38,   14,   14,   14, 0x05,
      49,   14,   14,   14, 0x05,
      74,   61,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     106,   14,   14,   14, 0x0a,
     113,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ChatContainer[] = {
    "ChatContainer\0\0BackShow()\0FrontShow()\0"
    "BackHide()\0FrontHide()\0browser,html\0"
    "SetHtml(QTextBrowser*,QString*)\0Back()\0"
    "Front()\0"
};

void ChatContainer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ChatContainer *_t = static_cast<ChatContainer *>(_o);
        switch (_id) {
        case 0: _t->BackShow(); break;
        case 1: _t->FrontShow(); break;
        case 2: _t->BackHide(); break;
        case 3: _t->FrontHide(); break;
        case 4: _t->SetHtml((*reinterpret_cast< QTextBrowser*(*)>(_a[1])),(*reinterpret_cast< QString*(*)>(_a[2]))); break;
        case 5: _t->Back(); break;
        case 6: _t->Front(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ChatContainer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ChatContainer::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_ChatContainer,
      qt_meta_data_ChatContainer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ChatContainer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ChatContainer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ChatContainer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ChatContainer))
        return static_cast<void*>(const_cast< ChatContainer*>(this));
    return QFrame::qt_metacast(_clname);
}

int ChatContainer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void ChatContainer::BackShow()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ChatContainer::FrontShow()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void ChatContainer::BackHide()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void ChatContainer::FrontHide()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void ChatContainer::SetHtml(QTextBrowser * _t1, QString * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
