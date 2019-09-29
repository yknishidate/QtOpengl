/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../QtOpengl/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[18];
    char stringdata0[414];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 22), // "on_colorButton_clicked"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 23), // "on_actionCube_triggered"
QT_MOC_LITERAL(4, 59, 25), // "on_actionSphere_triggered"
QT_MOC_LITERAL(5, 85, 24), // "on_colorButton_2_clicked"
QT_MOC_LITERAL(6, 110, 25), // "on_actionRender_triggered"
QT_MOC_LITERAL(7, 136, 24), // "on_actionPlane_triggered"
QT_MOC_LITERAL(8, 161, 26), // "on_actionWireframe_toggled"
QT_MOC_LITERAL(9, 188, 4), // "arg1"
QT_MOC_LITERAL(10, 193, 33), // "on_actionBackface_Culling_tog..."
QT_MOC_LITERAL(11, 227, 30), // "on_actionDepth_Testing_toggled"
QT_MOC_LITERAL(12, 258, 27), // "on_transColorButton_clicked"
QT_MOC_LITERAL(13, 286, 43), // "on_materialTypeComboBox_curre..."
QT_MOC_LITERAL(14, 330, 5), // "index"
QT_MOC_LITERAL(15, 336, 27), // "on_lightColorButton_clicked"
QT_MOC_LITERAL(16, 364, 26), // "on_radSpinBox_valueChanged"
QT_MOC_LITERAL(17, 391, 22) // "on_segBox_valueChanged"

    },
    "MainWindow\0on_colorButton_clicked\0\0"
    "on_actionCube_triggered\0"
    "on_actionSphere_triggered\0"
    "on_colorButton_2_clicked\0"
    "on_actionRender_triggered\0"
    "on_actionPlane_triggered\0"
    "on_actionWireframe_toggled\0arg1\0"
    "on_actionBackface_Culling_toggled\0"
    "on_actionDepth_Testing_toggled\0"
    "on_transColorButton_clicked\0"
    "on_materialTypeComboBox_currentIndexChanged\0"
    "index\0on_lightColorButton_clicked\0"
    "on_radSpinBox_valueChanged\0"
    "on_segBox_valueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    0,   87,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    0,   89,    2, 0x08 /* Private */,
       8,    1,   90,    2, 0x08 /* Private */,
      10,    1,   93,    2, 0x08 /* Private */,
      11,    1,   96,    2, 0x08 /* Private */,
      12,    0,   99,    2, 0x08 /* Private */,
      13,    1,  100,    2, 0x08 /* Private */,
      15,    0,  103,    2, 0x08 /* Private */,
      16,    1,  104,    2, 0x08 /* Private */,
      17,    1,  107,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    9,
    QMetaType::Void, QMetaType::Int,    9,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_colorButton_clicked(); break;
        case 1: _t->on_actionCube_triggered(); break;
        case 2: _t->on_actionSphere_triggered(); break;
        case 3: _t->on_colorButton_2_clicked(); break;
        case 4: _t->on_actionRender_triggered(); break;
        case 5: _t->on_actionPlane_triggered(); break;
        case 6: _t->on_actionWireframe_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_actionBackface_Culling_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_actionDepth_Testing_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_transColorButton_clicked(); break;
        case 10: _t->on_materialTypeComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_lightColorButton_clicked(); break;
        case 12: _t->on_radSpinBox_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: _t->on_segBox_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
