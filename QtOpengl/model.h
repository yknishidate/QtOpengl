#ifndef MODEL_H
#define MODEL_H

#include "mesh.h"

class Model
{
public:
    Model(const QString& fileName);

    void setTexture(QString fileName);
    void draw(QOpenGLShaderProgram *shader_program, GLenum displayMode);

    std::string name;

    Mesh *mesh;
    //Texture texture;
    QOpenGLTexture *texture;

    QVector3D position;
    QVector3D scale;
    QVector3D rotation;
};

#endif // MODEL_H
