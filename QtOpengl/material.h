#ifndef MATERIAL_H
#define MATERIAL_H
#include <QVector3D>

struct Material{
    int type;

    QVector3D ambient;
    QVector3D diffuse;
    QVector3D specular;
    float shininess;
};

#endif // MATERIAL_H
