/****************************************************************************
** Meta object code from reading C++ file 'targetlist.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gcs/src/targetlist.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'targetlist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TargetList_t {
    QByteArrayData data[6];
    char stringdata0[51];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TargetList_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TargetList_t qt_meta_stringdata_TargetList = {
    {
QT_MOC_LITERAL(0, 0, 10), // "TargetList"
QT_MOC_LITERAL(1, 11, 9), // "newTarget"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 7), // "Target*"
QT_MOC_LITERAL(4, 30, 6), // "update"
QT_MOC_LITERAL(5, 37, 13) // "updateDisplay"

    },
    "TargetList\0newTarget\0\0Target*\0update\0"
    "updateDisplay"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TargetList[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    1,   32,    2, 0x06 /* Public */,
       5,    1,   35,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void TargetList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TargetList *_t = static_cast<TargetList *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newTarget((*reinterpret_cast< Target*(*)>(_a[1]))); break;
        case 1: _t->update((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->updateDisplay((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TargetList::*_t)(Target * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TargetList::newTarget)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TargetList::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TargetList::update)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (TargetList::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TargetList::updateDisplay)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject TargetList::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TargetList.data,
      qt_meta_data_TargetList,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TargetList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TargetList::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TargetList.stringdata0))
        return static_cast<void*>(const_cast< TargetList*>(this));
    return QObject::qt_metacast(_clname);
}

int TargetList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void TargetList::newTarget(Target * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TargetList::update(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TargetList::updateDisplay(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE