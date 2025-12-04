/****************************************************************************
** Meta object code from reading C++ file 'v9mqtt.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../v9mqtt.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'v9mqtt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_V9Mqtt_t {
    QByteArrayData data[15];
    char stringdata0[253];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_V9Mqtt_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_V9Mqtt_t qt_meta_stringdata_V9Mqtt = {
    {
QT_MOC_LITERAL(0, 0, 6), // "V9Mqtt"
QT_MOC_LITERAL(1, 7, 28), // "on_pushButton_server_clicked"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 7), // "checked"
QT_MOC_LITERAL(4, 45, 17), // "stateChanged_slot"
QT_MOC_LITERAL(5, 63, 24), // "QMqttClient::ClientState"
QT_MOC_LITERAL(6, 88, 5), // "state"
QT_MOC_LITERAL(7, 94, 20), // "messageReceived_slot"
QT_MOC_LITERAL(8, 115, 7), // "message"
QT_MOC_LITERAL(9, 123, 14), // "QMqttTopicName"
QT_MOC_LITERAL(10, 138, 5), // "topic"
QT_MOC_LITERAL(11, 144, 26), // "on_pushButton_led1_clicked"
QT_MOC_LITERAL(12, 171, 26), // "on_pushButton_led2_clicked"
QT_MOC_LITERAL(13, 198, 26), // "on_pushButton_beep_clicked"
QT_MOC_LITERAL(14, 225, 27) // "on_pushButton_relay_clicked"

    },
    "V9Mqtt\0on_pushButton_server_clicked\0"
    "\0checked\0stateChanged_slot\0"
    "QMqttClient::ClientState\0state\0"
    "messageReceived_slot\0message\0"
    "QMqttTopicName\0topic\0on_pushButton_led1_clicked\0"
    "on_pushButton_led2_clicked\0"
    "on_pushButton_beep_clicked\0"
    "on_pushButton_relay_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_V9Mqtt[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x08 /* Private */,
       4,    1,   52,    2, 0x08 /* Private */,
       7,    2,   55,    2, 0x08 /* Private */,
      11,    1,   60,    2, 0x08 /* Private */,
      12,    1,   63,    2, 0x08 /* Private */,
      13,    1,   66,    2, 0x08 /* Private */,
      14,    1,   69,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, QMetaType::QByteArray, 0x80000000 | 9,    8,   10,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,

       0        // eod
};

void V9Mqtt::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<V9Mqtt *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_server_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->stateChanged_slot((*reinterpret_cast< QMqttClient::ClientState(*)>(_a[1]))); break;
        case 2: _t->messageReceived_slot((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< const QMqttTopicName(*)>(_a[2]))); break;
        case 3: _t->on_pushButton_led1_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->on_pushButton_led2_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_pushButton_beep_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->on_pushButton_relay_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject V9Mqtt::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_V9Mqtt.data,
    qt_meta_data_V9Mqtt,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *V9Mqtt::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *V9Mqtt::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_V9Mqtt.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int V9Mqtt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
