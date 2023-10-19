/****************************************************************************
** Meta object code from reading C++ file 'mywindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../ModeleBarwWiki/mywindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mywindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyWindow_t {
    QByteArrayData data[17];
    char stringdata0[147];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyWindow_t qt_meta_stringdata_MyWindow = {
    {
QT_MOC_LITERAL(0, 0, 8), // "MyWindow"
QT_MOC_LITERAL(1, 9, 10), // "slot_czysc"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 12), // "RGBsliderRed"
QT_MOC_LITERAL(4, 34, 1), // "r"
QT_MOC_LITERAL(5, 36, 14), // "RGBsliderGreen"
QT_MOC_LITERAL(6, 51, 1), // "g"
QT_MOC_LITERAL(7, 53, 13), // "RGBsliderBlue"
QT_MOC_LITERAL(8, 67, 1), // "b"
QT_MOC_LITERAL(9, 69, 12), // "HSVsliderHue"
QT_MOC_LITERAL(10, 82, 1), // "h"
QT_MOC_LITERAL(11, 84, 19), // "HSVsliderSaturation"
QT_MOC_LITERAL(12, 104, 1), // "s"
QT_MOC_LITERAL(13, 106, 14), // "HSVsliderValue"
QT_MOC_LITERAL(14, 121, 1), // "v"
QT_MOC_LITERAL(15, 123, 10), // "paintEvent"
QT_MOC_LITERAL(16, 134, 12) // "QPaintEvent*"

    },
    "MyWindow\0slot_czysc\0\0RGBsliderRed\0r\0"
    "RGBsliderGreen\0g\0RGBsliderBlue\0b\0"
    "HSVsliderHue\0h\0HSVsliderSaturation\0s\0"
    "HSVsliderValue\0v\0paintEvent\0QPaintEvent*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    1,   55,    2, 0x08 /* Private */,
       5,    1,   58,    2, 0x08 /* Private */,
       7,    1,   61,    2, 0x08 /* Private */,
       9,    1,   64,    2, 0x08 /* Private */,
      11,    1,   67,    2, 0x08 /* Private */,
      13,    1,   70,    2, 0x08 /* Private */,
      15,    1,   73,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, 0x80000000 | 16,    2,

       0        // eod
};

void MyWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_czysc(); break;
        case 1: _t->RGBsliderRed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->RGBsliderGreen((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->RGBsliderBlue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->HSVsliderHue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->HSVsliderSaturation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->HSVsliderValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->paintEvent((*reinterpret_cast< QPaintEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MyWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_MyWindow.data,
    qt_meta_data_MyWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MyWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MyWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
