#ifndef MODEL_H
#define MODEL_H

#include "mesh.h"
#include "material.h"

class Model
{
public:
    Model(const QString& fileName);
    Model(const int type);
    std::string getName(){return name;}
    int getType(){return type;}

    // Coordinates
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

    // Color
    void setMaterialDiffColor(QColor color);
    QColor getMaterialDiffColor(){return QColor( material.diffuse[0]*255.0f, material.diffuse[1]*255.0f, material.diffuse[2]*255.0f);}
    void setMaterialSpecColor(QColor color);
    QColor getMaterialSpecColor(){return QColor( material.specular[0]*255.0f, material.specular[1]*255.0f, material.specular[2]*255.0f);}
    void setShininess(int shine);
    int getShininess(){return material.shininess;}

    // Texture
    void setTexture(QString fileName);
    QString getTextureName();

    void draw(QOpenGLShaderProgram *shader_program, GLenum displayMode);

private:
    std::string name;
    int type;
    Mesh *mesh;

    // Coordinates
    QVector3D position;
    QVector3D scale;
    QVector3D rotation;

    // Material
    QOpenGLTexture *texture;
    QString textureName;
    Material material;
};

#endif // MODEL_H
