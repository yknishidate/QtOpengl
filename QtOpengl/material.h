#ifndef MATERIAL_H
#define MATERIAL_H
#include <QVector3D>
#include <QVector4D>

struct Material{
    int type;

    QVector3D ambient;
    QVector3D diffuse;
    QVector3D specular;
    float shininess;

    QVector4D transparentColor;
};

#endif // MATERIAL_H
