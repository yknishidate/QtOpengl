#ifndef MODEL_H
#define MODEL_H

#include "mesh.h"
#include "material.h"

class Model
{
public:
    Model(const QString& fileName);

    std::string getName(){return name;}

    void  setPositionX(double x){position.setX(x);}
    void  setPositionY(double y){position.setY(y);}
    void  setPositionZ(double z){position.setZ(z);}
    void  setScaleX(double x){scale.setX(x);}
    void  setScaleY(double y){scale.setY(y);}
    void  setScaleZ(double z){scale.setZ(z);}
    void  setRotationX(double x){rotation.setX(x);}
    void  setRotationY(double y){rotation.setY(y);}
    void  setRotationZ(double z){rotation.setZ(z);}

    QVector3D getPosition(){return position;}
    QVector3D getScale(){return scale;}
    QVector3D getRotation(){return rotation;}

    void setTexture(QString fileName);
    QString getTextureName();
    void draw(QOpenGLShaderProgram *shader_program, GLenum displayMode);

    Mesh *mesh;

private:
    std::string name;
    QOpenGLTexture *texture;
    QString textureName;
    QVector3D position;
    QVector3D scale;
    QVector3D rotation;
    Material material;
};

#endif // MODEL_H
