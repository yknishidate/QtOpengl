/****************************************************************************
** Meta object code from reading C++ file 'glwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../QtOpengl/glwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'glwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GLWidget_t {
    QByteArrayData data[82];
    char stringdata0[1096];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GLWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GLWidget_t qt_meta_stringdata_GLWidget = {
    {
QT_MOC_LITERAL(0, 0, 8), // "GLWidget"
QT_MOC_LITERAL(1, 9, 16), // "xRotationChanged"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 5), // "angle"
QT_MOC_LITERAL(4, 33, 16), // "yRotationChanged"
QT_MOC_LITERAL(5, 50, 16), // "zRotationChanged"
QT_MOC_LITERAL(6, 67, 10), // "loadedMesh"
QT_MOC_LITERAL(7, 78, 11), // "std::string"
QT_MOC_LITERAL(8, 90, 4), // "name"
QT_MOC_LITERAL(9, 95, 11), // "loadedModel"
QT_MOC_LITERAL(10, 107, 6), // "Model*"
QT_MOC_LITERAL(11, 114, 13), // "loadedTexture"
QT_MOC_LITERAL(12, 128, 19), // "setSpinboxPositionX"
QT_MOC_LITERAL(13, 148, 1), // "n"
QT_MOC_LITERAL(14, 150, 19), // "setSpinboxPositionY"
QT_MOC_LITERAL(15, 170, 19), // "setSpinboxPositionZ"
QT_MOC_LITERAL(16, 190, 16), // "setSpinboxScaleX"
QT_MOC_LITERAL(17, 207, 16), // "setSpinboxScaleY"
QT_MOC_LITERAL(18, 224, 16), // "setSpinboxScaleZ"
QT_MOC_LITERAL(19, 241, 19), // "setSpinboxRotationX"
QT_MOC_LITERAL(20, 261, 19), // "setSpinboxRotationY"
QT_MOC_LITERAL(21, 281, 19), // "setSpinboxRotationZ"
QT_MOC_LITERAL(22, 301, 15), // "setMeterialType"
QT_MOC_LITERAL(23, 317, 4), // "type"
QT_MOC_LITERAL(24, 322, 14), // "setColorButton"
QT_MOC_LITERAL(25, 337, 5), // "color"
QT_MOC_LITERAL(26, 343, 16), // "setColorButton_2"
QT_MOC_LITERAL(27, 360, 19), // "setTransColorButton"
QT_MOC_LITERAL(28, 380, 19), // "setLightColorButton"
QT_MOC_LITERAL(29, 400, 18), // "setShininessSlider"
QT_MOC_LITERAL(30, 419, 5), // "shine"
QT_MOC_LITERAL(31, 425, 13), // "setIorSpinBox"
QT_MOC_LITERAL(32, 439, 1), // "i"
QT_MOC_LITERAL(33, 441, 14), // "setTextureName"
QT_MOC_LITERAL(34, 456, 1), // "s"
QT_MOC_LITERAL(35, 458, 19), // "setSphereRadSpinBox"
QT_MOC_LITERAL(36, 478, 1), // "r"
QT_MOC_LITERAL(37, 480, 19), // "setSphereSegSpinBox"
QT_MOC_LITERAL(38, 500, 2), // "st"
QT_MOC_LITERAL(39, 503, 14), // "sphereSelected"
QT_MOC_LITERAL(40, 518, 3), // "arg"
QT_MOC_LITERAL(41, 522, 12), // "cubeSelected"
QT_MOC_LITERAL(42, 535, 14), // "setMeterialIor"
QT_MOC_LITERAL(43, 550, 12), // "setXRotation"
QT_MOC_LITERAL(44, 563, 12), // "setYRotation"
QT_MOC_LITERAL(45, 576, 12), // "setZRotation"
QT_MOC_LITERAL(46, 589, 14), // "setDisplayMode"
QT_MOC_LITERAL(47, 604, 11), // "setCullFace"
QT_MOC_LITERAL(48, 616, 12), // "setDepthTest"
QT_MOC_LITERAL(49, 629, 20), // "changeModelPositionX"
QT_MOC_LITERAL(50, 650, 1), // "x"
QT_MOC_LITERAL(51, 652, 20), // "changeModelPositionY"
QT_MOC_LITERAL(52, 673, 1), // "y"
QT_MOC_LITERAL(53, 675, 20), // "changeModelPositionZ"
QT_MOC_LITERAL(54, 696, 1), // "z"
QT_MOC_LITERAL(55, 698, 17), // "changeModelScaleX"
QT_MOC_LITERAL(56, 716, 17), // "changeModelScaleY"
QT_MOC_LITERAL(57, 734, 17), // "changeModelScaleZ"
QT_MOC_LITERAL(58, 752, 20), // "changeModelRotationX"
QT_MOC_LITERAL(59, 773, 20), // "changeModelRotationY"
QT_MOC_LITERAL(60, 794, 20), // "changeModelRotationZ"
QT_MOC_LITERAL(61, 815, 4), // "open"
QT_MOC_LITERAL(62, 820, 15), // "createPrimitive"
QT_MOC_LITERAL(63, 836, 11), // "openTexture"
QT_MOC_LITERAL(64, 848, 13), // "selectedModel"
QT_MOC_LITERAL(65, 862, 11), // "QModelIndex"
QT_MOC_LITERAL(66, 874, 10), // "modelIndex"
QT_MOC_LITERAL(67, 885, 12), // "createSphere"
QT_MOC_LITERAL(68, 898, 2), // "sl"
QT_MOC_LITERAL(69, 901, 12), // "changeSphere"
QT_MOC_LITERAL(70, 914, 15), // "changeSphereRad"
QT_MOC_LITERAL(71, 930, 15), // "changeSphereSeg"
QT_MOC_LITERAL(72, 946, 18), // "changeMeterialType"
QT_MOC_LITERAL(73, 965, 1), // "t"
QT_MOC_LITERAL(74, 967, 20), // "setMaterialDiffColor"
QT_MOC_LITERAL(75, 988, 20), // "setMaterialSpecColor"
QT_MOC_LITERAL(76, 1009, 21), // "setMaterialTransColor"
QT_MOC_LITERAL(77, 1031, 12), // "setShininess"
QT_MOC_LITERAL(78, 1044, 21), // "setMaterialLightColor"
QT_MOC_LITERAL(79, 1066, 14), // "setMaterialIor"
QT_MOC_LITERAL(80, 1081, 11), // "deleteModel"
QT_MOC_LITERAL(81, 1093, 2) // "id"

    },
    "GLWidget\0xRotationChanged\0\0angle\0"
    "yRotationChanged\0zRotationChanged\0"
    "loadedMesh\0std::string\0name\0loadedModel\0"
    "Model*\0loadedTexture\0setSpinboxPositionX\0"
    "n\0setSpinboxPositionY\0setSpinboxPositionZ\0"
    "setSpinboxScaleX\0setSpinboxScaleY\0"
    "setSpinboxScaleZ\0setSpinboxRotationX\0"
    "setSpinboxRotationY\0setSpinboxRotationZ\0"
    "setMeterialType\0type\0setColorButton\0"
    "color\0setColorButton_2\0setTransColorButton\0"
    "setLightColorButton\0setShininessSlider\0"
    "shine\0setIorSpinBox\0i\0setTextureName\0"
    "s\0setSphereRadSpinBox\0r\0setSphereSegSpinBox\0"
    "st\0sphereSelected\0arg\0cubeSelected\0"
    "setMeterialIor\0setXRotation\0setYRotation\0"
    "setZRotation\0setDisplayMode\0setCullFace\0"
    "setDepthTest\0changeModelPositionX\0x\0"
    "changeModelPositionY\0y\0changeModelPositionZ\0"
    "z\0changeModelScaleX\0changeModelScaleY\0"
    "changeModelScaleZ\0changeModelRotationX\0"
    "changeModelRotationY\0changeModelRotationZ\0"
    "open\0createPrimitive\0openTexture\0"
    "selectedModel\0QModelIndex\0modelIndex\0"
    "createSphere\0sl\0changeSphere\0"
    "changeSphereRad\0changeSphereSeg\0"
    "changeMeterialType\0t\0setMaterialDiffColor\0"
    "setMaterialSpecColor\0setMaterialTransColor\0"
    "setShininess\0setMaterialLightColor\0"
    "setMaterialIor\0deleteModel\0id"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GLWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      59,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      28,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  309,    2, 0x06 /* Public */,
       4,    1,  312,    2, 0x06 /* Public */,
       5,    1,  315,    2, 0x06 /* Public */,
       6,    1,  318,    2, 0x06 /* Public */,
       9,    1,  321,    2, 0x06 /* Public */,
      11,    1,  324,    2, 0x06 /* Public */,
      12,    1,  327,    2, 0x06 /* Public */,
      14,    1,  330,    2, 0x06 /* Public */,
      15,    1,  333,    2, 0x06 /* Public */,
      16,    1,  336,    2, 0x06 /* Public */,
      17,    1,  339,    2, 0x06 /* Public */,
      18,    1,  342,    2, 0x06 /* Public */,
      19,    1,  345,    2, 0x06 /* Public */,
      20,    1,  348,    2, 0x06 /* Public */,
      21,    1,  351,    2, 0x06 /* Public */,
      22,    1,  354,    2, 0x06 /* Public */,
      24,    1,  357,    2, 0x06 /* Public */,
      26,    1,  360,    2, 0x06 /* Public */,
      27,    1,  363,    2, 0x06 /* Public */,
      28,    1,  366,    2, 0x06 /* Public */,
      29,    1,  369,    2, 0x06 /* Public */,
      31,    1,  372,    2, 0x06 /* Public */,
      33,    1,  375,    2, 0x06 /* Public */,
      35,    1,  378,    2, 0x06 /* Public */,
      37,    1,  381,    2, 0x06 /* Public */,
      39,    1,  384,    2, 0x06 /* Public */,
      41,    1,  387,    2, 0x06 /* Public */,
      42,    1,  390,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      43,    1,  393,    2, 0x0a /* Public */,
      44,    1,  396,    2, 0x0a /* Public */,
      45,    1,  399,    2, 0x0a /* Public */,
      46,    1,  402,    2, 0x0a /* Public */,
      47,    1,  405,    2, 0x0a /* Public */,
      48,    1,  408,    2, 0x0a /* Public */,
      49,    1,  411,    2, 0x0a /* Public */,
      51,    1,  414,    2, 0x0a /* Public */,
      53,    1,  417,    2, 0x0a /* Public */,
      55,    1,  420,    2, 0x0a /* Public */,
      56,    1,  423,    2, 0x0a /* Public */,
      57,    1,  426,    2, 0x0a /* Public */,
      58,    1,  429,    2, 0x0a /* Public */,
      59,    1,  432,    2, 0x0a /* Public */,
      60,    1,  435,    2, 0x0a /* Public */,
      61,    0,  438,    2, 0x0a /* Public */,
      62,    1,  439,    2, 0x0a /* Public */,
      63,    0,  442,    2, 0x0a /* Public */,
      64,    1,  443,    2, 0x0a /* Public */,
      67,    3,  446,    2, 0x0a /* Public */,
      69,    3,  453,    2, 0x0a /* Public */,
      70,    1,  460,    2, 0x0a /* Public */,
      71,    1,  463,    2, 0x0a /* Public */,
      72,    1,  466,    2, 0x0a /* Public */,
      74,    1,  469,    2, 0x0a /* Public */,
      75,    1,  472,    2, 0x0a /* Public */,
      76,    1,  475,    2, 0x0a /* Public */,
      77,    1,  478,    2, 0x0a /* Public */,
      78,    1,  481,    2, 0x0a /* Public */,
      79,    1,  484,    2, 0x0a /* Public */,
      80,    1,  487,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 10,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Double,   13,
    QMetaType::Void, QMetaType::Double,   13,
    QMetaType::Void, QMetaType::Double,   13,
    QMetaType::Void, QMetaType::Double,   13,
    QMetaType::Void, QMetaType::Double,   13,
    QMetaType::Void, QMetaType::Double,   13,
    QMetaType::Void, QMetaType::Double,   13,
    QMetaType::Void, QMetaType::Double,   13,
    QMetaType::Void, QMetaType::Double,   13,
    QMetaType::Void, QMetaType::Int,   23,
    QMetaType::Void, QMetaType::QColor,   25,
    QMetaType::Void, QMetaType::QColor,   25,
    QMetaType::Void, QMetaType::QColor,   25,
    QMetaType::Void, QMetaType::QColor,   25,
    QMetaType::Void, QMetaType::Int,   30,
    QMetaType::Void, QMetaType::Double,   32,
    QMetaType::Void, QMetaType::QString,   34,
    QMetaType::Void, QMetaType::Double,   36,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::Bool,   40,
    QMetaType::Void, QMetaType::Bool,   40,
    QMetaType::Void, QMetaType::Float,   32,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Bool,   40,
    QMetaType::Void, QMetaType::Bool,   40,
    QMetaType::Void, QMetaType::Bool,   40,
    QMetaType::Void, QMetaType::Double,   50,
    QMetaType::Void, QMetaType::Double,   52,
    QMetaType::Void, QMetaType::Double,   54,
    QMetaType::Void, QMetaType::Double,   50,
    QMetaType::Void, QMetaType::Double,   52,
    QMetaType::Void, QMetaType::Double,   54,
    QMetaType::Void, QMetaType::Double,   50,
    QMetaType::Void, QMetaType::Double,   52,
    QMetaType::Void, QMetaType::Double,   54,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   23,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 65,   66,
    QMetaType::Void, QMetaType::Float, QMetaType::Int, QMetaType::Int,   36,   38,   68,
    QMetaType::Void, QMetaType::Float, QMetaType::Int, QMetaType::Int,   36,   38,   68,
    QMetaType::Void, QMetaType::Float,   36,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::Int,   73,
    QMetaType::Void, QMetaType::QColor,   25,
    QMetaType::Void, QMetaType::QColor,   25,
    QMetaType::Void, QMetaType::QColor,   25,
    QMetaType::Void, QMetaType::Int,   30,
    QMetaType::Void, QMetaType::QColor,   25,
    QMetaType::Void, QMetaType::Double,   32,
    QMetaType::Void, QMetaType::Int,   81,

       0        // eod
};

void GLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GLWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->xRotationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->yRotationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->zRotationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->loadedMesh((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 4: _t->loadedModel((*reinterpret_cast< Model*(*)>(_a[1]))); break;
        case 5: _t->loadedTexture((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->setSpinboxPositionX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->setSpinboxPositionY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->setSpinboxPositionZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: _t->setSpinboxScaleX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->setSpinboxScaleY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->setSpinboxScaleZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: _t->setSpinboxRotationX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: _t->setSpinboxRotationY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: _t->setSpinboxRotationZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 15: _t->setMeterialType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->setColorButton((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 17: _t->setColorButton_2((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 18: _t->setTransColorButton((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 19: _t->setLightColorButton((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 20: _t->setShininessSlider((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->setIorSpinBox((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 22: _t->setTextureName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 23: _t->setSphereRadSpinBox((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 24: _t->setSphereSegSpinBox((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->sphereSelected((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 26: _t->cubeSelected((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 27: _t->setMeterialIor((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 28: _t->setXRotation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 29: _t->setYRotation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 30: _t->setZRotation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 31: _t->setDisplayMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 32: _t->setCullFace((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 33: _t->setDepthTest((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 34: _t->changeModelPositionX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 35: _t->changeModelPositionY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 36: _t->changeModelPositionZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 37: _t->changeModelScaleX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 38: _t->changeModelScaleY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 39: _t->changeModelScaleZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 40: _t->changeModelRotationX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 41: _t->changeModelRotationY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 42: _t->changeModelRotationZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 43: _t->open(); break;
        case 44: _t->createPrimitive((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 45: _t->openTexture(); break;
        case 46: _t->selectedModel((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 47: _t->createSphere((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 48: _t->changeSphere((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 49: _t->changeSphereRad((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 50: _t->changeSphereSeg((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 51: _t->changeMeterialType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 52: _t->setMaterialDiffColor((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 53: _t->setMaterialSpecColor((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 54: _t->setMaterialTransColor((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 55: _t->setShininess((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 56: _t->setMaterialLightColor((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 57: _t->setMaterialIor((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 58: _t->deleteModel((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GLWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::xRotationChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::yRotationChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::zRotationChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::loadedMesh)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(Model * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::loadedModel)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::loadedTexture)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::setSpinboxPositionX)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::setSpinboxPositionY)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::setSpinboxPositionZ)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::setSpinboxScaleX)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::setSpinboxScaleY)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::setSpinboxScaleZ)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::setSpinboxRotationX)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::setSpinboxRotationY)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::setSpinboxRotationZ)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::setMeterialType)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(QColor );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::setColorButton)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(QColor );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::setColorButton_2)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(QColor );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::setTransColorButton)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(QColor );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::setLightColorButton)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::setShininessSlider)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::setIorSpinBox)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::setTextureName)) {
                *result = 22;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::setSphereRadSpinBox)) {
                *result = 23;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::setSphereSegSpinBox)) {
                *result = 24;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::sphereSelected)) {
                *result = 25;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::cubeSelected)) {
                *result = 26;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::setMeterialIor)) {
                *result = 27;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GLWidget::staticMetaObject = { {
    &QOpenGLWidget::staticMetaObject,
    qt_meta_stringdata_GLWidget.data,
    qt_meta_data_GLWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GLWidget.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QOpenGLFunctions"))
        return static_cast< QOpenGLFunctions*>(this);
    return QOpenGLWidget::qt_metacast(_clname);
}

int GLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 59)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 59;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 59)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 59;
    }
    return _id;
}

// SIGNAL 0
void GLWidget::xRotationChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GLWidget::yRotationChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GLWidget::zRotationChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GLWidget::loadedMesh(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GLWidget::loadedModel(Model * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void GLWidget::loadedTexture(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void GLWidget::setSpinboxPositionX(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void GLWidget::setSpinboxPositionY(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void GLWidget::setSpinboxPositionZ(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void GLWidget::setSpinboxScaleX(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void GLWidget::setSpinboxScaleY(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void GLWidget::setSpinboxScaleZ(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void GLWidget::setSpinboxRotationX(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void GLWidget::setSpinboxRotationY(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void GLWidget::setSpinboxRotationZ(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void GLWidget::setMeterialType(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void GLWidget::setColorButton(QColor _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void GLWidget::setColorButton_2(QColor _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void GLWidget::setTransColorButton(QColor _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void GLWidget::setLightColorButton(QColor _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void GLWidget::setShininessSlider(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void GLWidget::setIorSpinBox(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void GLWidget::setTextureName(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void GLWidget::setSphereRadSpinBox(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 23, _a);
}

// SIGNAL 24
void GLWidget::setSphereSegSpinBox(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 24, _a);
}

// SIGNAL 25
void GLWidget::sphereSelected(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 25, _a);
}

// SIGNAL 26
void GLWidget::cubeSelected(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 26, _a);
}

// SIGNAL 27
void GLWidget::setMeterialIor(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 27, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
