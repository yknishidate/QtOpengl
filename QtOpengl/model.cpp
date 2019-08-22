#include "model.h"

Model::Model(const QString& fileName)
{
    mesh = new Mesh(fileName);
    name = mesh->getName();
    type = 0;

    position = QVector3D(0.0f, 0.0f, 0.0f);
    scale    = QVector3D(1.0f, 1.0f, 1.0f);
    rotation = QVector3D(0.0f, 0.0f, 0.0f);

    texture = nullptr;
    textureName = "";

    material.ambient = QVector3D(0.7f, 0.7f, 0.7f);
    material.diffuse = QVector3D(0.7f, 0.7f, 0.7f);
    material.specular = QVector3D(0.7f, 0.7f, 0.7f);
    material.shininess = 90.0f;
}

// Primitives
Model::Model(const int type){
    mesh = new Mesh(type);
    name = mesh->getName();

    position = QVector3D(0.0f, 0.0f, 0.0f);
    scale    = QVector3D(1.0f, 1.0f, 1.0f);
    rotation = QVector3D(0.0f, 0.0f, 0.0f);

    texture = nullptr;
    textureName = "";

    material.ambient = QVector3D(0.7f, 0.7f, 0.7f);
    material.diffuse = QVector3D(0.7f, 0.7f, 0.7f);
    material.specular = QVector3D(0.7f, 0.7f, 0.7f);
    material.shininess = 90.0f;
}

void Model::setTexture(QString fileName){
    textureName = fileName;
    texture = new QOpenGLTexture(QImage(fileName).mirrored());
    texture->setMinificationFilter(QOpenGLTexture::Nearest);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    texture->setWrapMode(QOpenGLTexture::Repeat);
}

void Model::draw(QOpenGLShaderProgram *shader_program, GLenum displayMode)
{
    shader_program->setUniformValue("Kamb", material.ambient);
    shader_program->setUniformValue("Kdiff", material.diffuse);
    shader_program->setUniformValue("Kspec", material.specular);
    shader_program->setUniformValue("Kshi", material.shininess);
    mesh->draw(shader_program, displayMode, texture);
}

QString Model::getTextureName(){
    return textureName;
}

void Model::setMaterialDiffColor(QColor color){
   material.diffuse[0] = material.ambient[0] = color.red()/255.0f;
   material.diffuse[1] = material.ambient[1] = color.green()/255.0f;
   material.diffuse[2] = material.ambient[2] = color.blue()/255.0f;
   qDebug() << "setMaterialColor";
}
void Model::setMaterialSpecColor(QColor color){
   material.specular[0] = color.red()/255.0f;
   material.specular[1] = color.green()/255.0f;
   material.specular[2] = color.blue()/255.0f;
   qDebug() << "setMaterialColor";
}

void Model::setShininess(int shine){
   material.shininess = shine;
   qDebug() << "set shininess";
}
