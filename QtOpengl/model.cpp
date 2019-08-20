#include "model.h"

Model::Model(const QString& fileName)
{
    mesh = new Mesh(fileName);
    name = mesh->getName();

    position = QVector3D(0.0f, 0.0f, 0.0f);
    scale    = QVector3D(1.0f, 1.0f, 1.0f);
    rotation = QVector3D(0.0f, 0.0f, 0.0f);

    texture = nullptr;
}

void Model::setTexture(QString fileName){
    texture = new QOpenGLTexture(QImage(fileName).mirrored());
    texture->setMinificationFilter(QOpenGLTexture::Nearest);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    texture->setWrapMode(QOpenGLTexture::Repeat);
}

void Model::draw(QOpenGLShaderProgram *shader_program, GLenum displayMode)
{
    mesh->draw(shader_program, displayMode, texture);
}
