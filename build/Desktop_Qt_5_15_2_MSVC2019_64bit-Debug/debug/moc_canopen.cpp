/****************************************************************************
** Meta object code from reading C++ file 'canopen.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../canopen.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'canopen.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CANopen_t {
    QByteArrayData data[15];
    char stringdata0[256];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CANopen_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CANopen_t qt_meta_stringdata_CANopen = {
    {
QT_MOC_LITERAL(0, 0, 7), // "CANopen"
QT_MOC_LITERAL(1, 8, 17), // "SigReceiveCanData"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 7), // "recv_id"
QT_MOC_LITERAL(4, 35, 3), // "dlc"
QT_MOC_LITERAL(5, 39, 4), // "data"
QT_MOC_LITERAL(6, 44, 29), // "on_pushButton_refresh_clicked"
QT_MOC_LITERAL(7, 74, 26), // "on_pushButton_open_clicked"
QT_MOC_LITERAL(8, 101, 7), // "checked"
QT_MOC_LITERAL(9, 109, 26), // "on_pushButton_led1_clicked"
QT_MOC_LITERAL(10, 136, 26), // "on_pushButton_led2_clicked"
QT_MOC_LITERAL(11, 163, 26), // "on_pushButton_beep_clicked"
QT_MOC_LITERAL(12, 190, 27), // "on_pushButton_relay_clicked"
QT_MOC_LITERAL(13, 218, 18), // "timer_timeout_slot"
QT_MOC_LITERAL(14, 237, 18) // "SlotReceiveCanData"

    },
    "CANopen\0SigReceiveCanData\0\0recv_id\0"
    "dlc\0data\0on_pushButton_refresh_clicked\0"
    "on_pushButton_open_clicked\0checked\0"
    "on_pushButton_led1_clicked\0"
    "on_pushButton_led2_clicked\0"
    "on_pushButton_beep_clicked\0"
    "on_pushButton_relay_clicked\0"
    "timer_timeout_slot\0SlotReceiveCanData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CANopen[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   66,    2, 0x08 /* Private */,
       7,    1,   67,    2, 0x08 /* Private */,
       9,    1,   70,    2, 0x08 /* Private */,
      10,    1,   73,    2, 0x08 /* Private */,
      11,    1,   76,    2, 0x08 /* Private */,
      12,    1,   79,    2, 0x08 /* Private */,
      13,    0,   82,    2, 0x08 /* Private */,
      14,    3,   83,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar, QMetaType::QByteArray,    3,    4,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar, QMetaType::QByteArray,    3,    4,    5,

       0        // eod
};

void CANopen::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CANopen *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SigReceiveCanData((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3]))); break;
        case 1: _t->on_pushButton_refresh_clicked(); break;
        case 2: _t->on_pushButton_open_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->on_pushButton_led1_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->on_pushButton_led2_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_pushButton_beep_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->on_pushButton_relay_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->timer_timeout_slot(); break;
        case 8: _t->SlotReceiveCanData((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CANopen::*)(quint32 , quint8 , QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CANopen::SigReceiveCanData)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CANopen::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CANopen.data,
    qt_meta_data_CANopen,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CANopen::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CANopen::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CANopen.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CANopen::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void CANopen::SigReceiveCanData(quint32 _t1, quint8 _t2, QByteArray _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
