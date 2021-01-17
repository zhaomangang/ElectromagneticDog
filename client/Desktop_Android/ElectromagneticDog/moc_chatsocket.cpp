/****************************************************************************
** Meta object code from reading C++ file 'chatsocket.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "chatsocket.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chatsocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ChatSocket_t {
    QByteArrayData data[11];
    char stringdata0[91];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ChatSocket_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ChatSocket_t qt_meta_stringdata_ChatSocket = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ChatSocket"
QT_MOC_LITERAL(1, 11, 12), // "logonSuccess"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 2), // "id"
QT_MOC_LITERAL(4, 28, 8), // "username"
QT_MOC_LITERAL(5, 37, 4), // "icon"
QT_MOC_LITERAL(6, 42, 11), // "logonFailed"
QT_MOC_LITERAL(7, 54, 19), // "slotConnectToServer"
QT_MOC_LITERAL(8, 74, 2), // "ip"
QT_MOC_LITERAL(9, 77, 4), // "port"
QT_MOC_LITERAL(10, 82, 8) // "slotRecv"

    },
    "ChatSocket\0logonSuccess\0\0id\0username\0"
    "icon\0logonFailed\0slotConnectToServer\0"
    "ip\0port\0slotRecv"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ChatSocket[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   34,    2, 0x06 /* Public */,
       6,    0,   41,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    2,   42,    2, 0x0a /* Public */,
      10,    0,   47,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString,    3,    4,    5,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::UInt,    8,    9,
    QMetaType::Void,

       0        // eod
};

void ChatSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ChatSocket *_t = static_cast<ChatSocket *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->logonSuccess((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: _t->logonFailed(); break;
        case 2: _t->slotConnectToServer((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 3: _t->slotRecv(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ChatSocket::*_t)(int , QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChatSocket::logonSuccess)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ChatSocket::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChatSocket::logonFailed)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ChatSocket::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ChatSocket.data,
      qt_meta_data_ChatSocket,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ChatSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChatSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ChatSocket.stringdata0))
        return static_cast<void*>(const_cast< ChatSocket*>(this));
    return QObject::qt_metacast(_clname);
}

int ChatSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ChatSocket::logonSuccess(int _t1, QString _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ChatSocket::logonFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
