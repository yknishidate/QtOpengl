#ifndef MODEL_H
#define MODEL_H

#include "mesh.h"

class Model
{
public:
    Model(const QString& fileName);

    std::string getName(){return name;}

    //float getPositionX(){return position.x();}
    void  setPositionX(double x){position.setX(x);}
    //float getPositionY(){return position.y();}
    void  setPositionY(double y){position.setY(y);}
    //float getPositionZ(){return position.z();}
    void  setPositionZ(double z){position.setZ(z);}

    //float getScaleX(){return scale.x();}
    void  setScaleX(double x){scale.setX(x);}
    //float getScaleY(){return scale.y();}
    void  setScaleY(double y){scale.setY(y);}
    //float getScaleZ(){return scale.z();}
    void  setScaleZ(double z){scale.setZ(z);}

    //float getRotationX(){return rotation.x();}
    void  setRotationX(double x){rotation.setX(x);}
    //float getRotationY(){return rotation.y();}
    void  setRotationY(double y){rotation.setY(y);}
    //float getRotationZ(){return rotation.z();}
    void  setRotationZ(double z){rotation.setZ(z);}

    QVector3D getPosition(){return position;}
    QVector3D getScale(){return scale;}
    QVector3D getRotation(){return rotation;}

    void setTexture(QString fileName);
    void draw(QOpenGLShaderProgram *shader_program, GLenum displayMode);

    Mesh *mesh;

private:
    std::string name;
    QOpenGLTexture *texture;
    QVector3D position;
    QVector3D scale;
    QVector3D rotation;
};

#endif // MODEL_H
