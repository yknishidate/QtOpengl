#include "spheremodel.h"

SphereModel::SphereModel(float r, int st, int sl):Model()
{
    rad = r;
    stacks = st;
    slices = sl;

    mesh = new Mesh();
    mesh->createSphere(rad, stacks, slices);
    name = mesh->getName();
    type = ModelType::SPHERE;

    position = QVector3D(0.0f, 0.0f, 0.0f);
    scale    = QVector3D(1.0f, 1.0f, 1.0f);
    rotation = QVector3D(0.0f, 0.0f, 0.0f);

    texture = nullptr;
    textureName = "";

    material.type = 0;
    material.ambient = QVector3D(0.7f, 0.7f, 0.7f);
    material.diffuse = QVector3D(0.7f, 0.7f, 0.7f);
    material.specular = QVector3D(1.0f, 1.0f, 1.0f);
    material.shininess = 16.0f;
    material.transparentColor = QVector4D(1.0f, 1.0f, 1.0f, 0.3f);
    material.lightColor = QVector4D(1.0f, 1.0f, 1.0f, 1.0f);
    material.ior = 1.5f;
}

void SphereModel::change(float r, int st, int sl)
{
    mesh->changeSphere(r, st, sl);
}
