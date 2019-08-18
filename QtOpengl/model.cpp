#include "model.h"

Model::Model(const QString& fileName)
{
    mesh = new Mesh(fileName);

    position = QVector3D(0.0f, 0.0f, 0.0f);
    scale = QVector3D(1.0f, 1.0f, 1.0f);
    rotation = QVector3D(0.0f, 0.0f, 0.0f);
}

void Model::setTexture(QString fileName){
    // Load Texture
    texture = new QOpenGLTexture(QImage(fileName).mirrored());
    // Minification -> Nearest
    texture->setMinificationFilter(QOpenGLTexture::Nearest);
    // Magnification -> Linear
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    // Repeat
    texture->setWrapMode(QOpenGLTexture::Repeat);
}

void Model::draw(QOpenGLShaderProgram *shader_program, GLenum displayMode)
{
    mesh->draw(shader_program, displayMode, texture);
}
