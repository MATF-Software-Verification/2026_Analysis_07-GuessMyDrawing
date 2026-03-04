/****************************************************************************
** Meta object code from reading C++ file 'client.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../07-GuessMyDrawing-master/07-GuessMyDrawing/Application/client.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Client_t {
    QByteArrayData data[26];
    char stringdata0[299];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Client_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Client_t qt_meta_stringdata_Client = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Client"
QT_MOC_LITERAL(1, 7, 15), // "messageReceived"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 6), // "sender"
QT_MOC_LITERAL(4, 31, 4), // "test"
QT_MOC_LITERAL(5, 36, 10), // "userJoined"
QT_MOC_LITERAL(6, 47, 8), // "username"
QT_MOC_LITERAL(7, 56, 8), // "userLeft"
QT_MOC_LITERAL(8, 65, 8), // "roomList"
QT_MOC_LITERAL(9, 74, 23), // "const QVector<QString>*"
QT_MOC_LITERAL(10, 98, 5), // "rooms"
QT_MOC_LITERAL(11, 104, 10), // "joinedRoom"
QT_MOC_LITERAL(12, 115, 5), // "bool&"
QT_MOC_LITERAL(13, 121, 7), // "success"
QT_MOC_LITERAL(14, 129, 13), // "youAreNewHost"
QT_MOC_LITERAL(15, 143, 15), // "errorConnecting"
QT_MOC_LITERAL(16, 159, 9), // "startGame"
QT_MOC_LITERAL(17, 169, 8), // "gameOver"
QT_MOC_LITERAL(18, 178, 14), // "canvasReceived"
QT_MOC_LITERAL(19, 193, 4), // "data"
QT_MOC_LITERAL(20, 198, 16), // "MessageReadyRead"
QT_MOC_LITERAL(21, 215, 16), // "connectedMessage"
QT_MOC_LITERAL(22, 232, 19), // "disconnectedMessage"
QT_MOC_LITERAL(23, 252, 5), // "error"
QT_MOC_LITERAL(24, 258, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(25, 287, 11) // "socketError"

    },
    "Client\0messageReceived\0\0sender\0test\0"
    "userJoined\0username\0userLeft\0roomList\0"
    "const QVector<QString>*\0rooms\0joinedRoom\0"
    "bool&\0success\0youAreNewHost\0errorConnecting\0"
    "startGame\0gameOver\0canvasReceived\0"
    "data\0MessageReadyRead\0connectedMessage\0"
    "disconnectedMessage\0error\0"
    "QAbstractSocket::SocketError\0socketError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Client[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   84,    2, 0x06 /* Public */,
       5,    1,   89,    2, 0x06 /* Public */,
       7,    1,   92,    2, 0x06 /* Public */,
       8,    1,   95,    2, 0x06 /* Public */,
      11,    1,   98,    2, 0x06 /* Public */,
      14,    0,  101,    2, 0x06 /* Public */,
      15,    0,  102,    2, 0x06 /* Public */,
      16,    0,  103,    2, 0x06 /* Public */,
      17,    0,  104,    2, 0x06 /* Public */,
      18,    1,  105,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      20,    0,  108,    2, 0x08 /* Private */,
      21,    0,  109,    2, 0x08 /* Private */,
      22,    0,  110,    2, 0x08 /* Private */,
      23,    1,  111,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   19,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 24,   25,

       0        // eod
};

void Client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Client *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->messageReceived((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->userJoined((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->userLeft((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->roomList((*reinterpret_cast< const QVector<QString>*(*)>(_a[1]))); break;
        case 4: _t->joinedRoom((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->youAreNewHost(); break;
        case 6: _t->errorConnecting(); break;
        case 7: _t->startGame(); break;
        case 8: _t->gameOver(); break;
        case 9: _t->canvasReceived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->MessageReadyRead(); break;
        case 11: _t->connectedMessage(); break;
        case 12: _t->disconnectedMessage(); break;
        case 13: _t->error((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Client::*)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::messageReceived)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Client::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::userJoined)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Client::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::userLeft)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Client::*)(const QVector<QString> * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::roomList)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Client::*)(bool & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::joinedRoom)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Client::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::youAreNewHost)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Client::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::errorConnecting)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Client::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::startGame)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (Client::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::gameOver)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (Client::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::canvasReceived)) {
                *result = 9;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Client::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Client.data,
    qt_meta_data_Client,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Client::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Client.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void Client::messageReceived(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Client::userJoined(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Client::userLeft(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Client::roomList(const QVector<QString> * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Client::joinedRoom(bool & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Client::youAreNewHost()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void Client::errorConnecting()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void Client::startGame()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void Client::gameOver()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void Client::canvasReceived(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
