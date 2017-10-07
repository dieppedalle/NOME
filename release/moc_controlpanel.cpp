/****************************************************************************
** Meta object code from reading C++ file 'controlpanel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../controlpanel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'controlpanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ControlPanel_t {
    QByteArrayData data[21];
    char stringdata0[296];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ControlPanel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ControlPanel_t qt_meta_stringdata_ControlPanel = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ControlPanel"
QT_MOC_LITERAL(1, 13, 14), // "makeOffsetMesh"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 4), // "test"
QT_MOC_LITERAL(4, 34, 16), // "viewContentReset"
QT_MOC_LITERAL(5, 51, 22), // "viewContentSetToSubdiv"
QT_MOC_LITERAL(6, 74, 5), // "level"
QT_MOC_LITERAL(7, 80, 28), // "viewContentSetToSubdivOffset"
QT_MOC_LITERAL(8, 109, 14), // "resetMinOffset"
QT_MOC_LITERAL(9, 124, 9), // "minOffset"
QT_MOC_LITERAL(10, 134, 14), // "resetMaxOffset"
QT_MOC_LITERAL(11, 149, 9), // "maxOffset"
QT_MOC_LITERAL(12, 159, 15), // "resetOffsetStep"
QT_MOC_LITERAL(13, 175, 10), // "offsetStep"
QT_MOC_LITERAL(14, 186, 17), // "offSetSliderMoved"
QT_MOC_LITERAL(15, 204, 14), // "resetForeColor"
QT_MOC_LITERAL(16, 219, 14), // "resetBackColor"
QT_MOC_LITERAL(17, 234, 17), // "vertexModeChecked"
QT_MOC_LITERAL(18, 252, 17), // "borderModeChecked"
QT_MOC_LITERAL(19, 270, 15), // "faceModeChecked"
QT_MOC_LITERAL(20, 286, 9) // "pushMerge"

    },
    "ControlPanel\0makeOffsetMesh\0\0test\0"
    "viewContentReset\0viewContentSetToSubdiv\0"
    "level\0viewContentSetToSubdivOffset\0"
    "resetMinOffset\0minOffset\0resetMaxOffset\0"
    "maxOffset\0resetOffsetStep\0offsetStep\0"
    "offSetSliderMoved\0resetForeColor\0"
    "resetBackColor\0vertexModeChecked\0"
    "borderModeChecked\0faceModeChecked\0"
    "pushMerge"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ControlPanel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   97,    2, 0x0a /* Public */,
       3,    1,  100,    2, 0x0a /* Public */,
       4,    0,  103,    2, 0x0a /* Public */,
       5,    1,  104,    2, 0x0a /* Public */,
       7,    0,  107,    2, 0x0a /* Public */,
       8,    1,  108,    2, 0x0a /* Public */,
      10,    1,  111,    2, 0x0a /* Public */,
      12,    1,  114,    2, 0x0a /* Public */,
      14,    0,  117,    2, 0x0a /* Public */,
      15,    1,  118,    2, 0x0a /* Public */,
      16,    1,  121,    2, 0x0a /* Public */,
      17,    1,  124,    2, 0x0a /* Public */,
      18,    1,  127,    2, 0x0a /* Public */,
      19,    1,  130,    2, 0x0a /* Public */,
      20,    1,  133,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,

       0        // eod
};

void ControlPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ControlPanel *_t = static_cast<ControlPanel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->makeOffsetMesh((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->test((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->test((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->viewContentReset(); break;
        case 4: _t->viewContentSetToSubdiv((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->viewContentSetToSubdivOffset(); break;
        case 6: _t->resetMinOffset((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->resetMaxOffset((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->resetOffsetStep((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->offSetSliderMoved(); break;
        case 10: _t->resetForeColor((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->resetBackColor((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->vertexModeChecked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->borderModeChecked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->faceModeChecked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->pushMerge((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ControlPanel::*_t)(float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ControlPanel::makeOffsetMesh)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject ControlPanel::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ControlPanel.data,
      qt_meta_data_ControlPanel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ControlPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ControlPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ControlPanel.stringdata0))
        return static_cast<void*>(const_cast< ControlPanel*>(this));
    return QWidget::qt_metacast(_clname);
}

int ControlPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void ControlPanel::makeOffsetMesh(float _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
