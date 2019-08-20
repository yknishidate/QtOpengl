#include "mesh.h"
#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QOpenGLExtraFunctions>


Mesh::Mesh()
{
}

Mesh::Mesh(const QString& fileName)
    : ibo(QOpenGLBuffer::IndexBuffer)
{
    init(OBJModel(fileName.toStdString()).ToIndexedModel());
}

Mesh::~Mesh()
{
    vbo.destroy();
    ibo.destroy();
}

void Mesh::init(const IndexedModel& model)
{
    qDebug() << "---initMesh()---";
    initializeOpenGLFunctions();

    texCoordOffset = model.positions.size()*sizeof(model.positions[0]);
    normalOffset   = texCoordOffset + model.texCoords.size()*sizeof(model.texCoords[0]);
    vboTotalSize   = normalOffset   + model.normals.size()*sizeof(model.normals[0]);

    vbo.create();
    vbo.bind();
    vbo.allocate( &model.positions[0], vboTotalSize);    // "&qvec[0]" で渡す
    vbo.write( texCoordOffset, &model.texCoords[0],
               model.texCoords.size()*sizeof(model.texCoords[0]));
    vbo.write( normalOffset, &model.normals[0],
               model.normals.size()*sizeof(model.normals[0]));
    //vbo.release();

    ibo.create();
    ibo.bind();
    ibo.allocate(&model.indices[0], model.indices.size() *sizeof(model.indices[0]));
    m_numIndices = model.indices.size();


    name = model.name;
    qDebug() << "Name   :" << QString::fromStdString(model.name);
    qDebug() << "Points :" << model.positions.size();
    qDebug() << "Indeces:" << model.indices.size();
    qDebug() << "vboTotalSize  :" << vboTotalSize;
    qDebug() << "vbo ID        :" << vbo.bufferId();
    qDebug() << "ibo ID        :" << ibo.bufferId();
}


void Mesh::draw(QOpenGLShaderProgram *shader_program, GLenum displayMode, QOpenGLTexture *texture)
{
    if(displayMode == GL_TRIANGLES && texture != nullptr){
        texture->bind();
    }else{
        glLineWidth(0.8f);
    }
    //shader_program->bind();
    vao.bind();
    ibo.bind();
    vbo.bind();

    shader_program->setAttributeBuffer(0, GL_FLOAT, 0, 3);  //stride = 0(default)
    shader_program->enableAttributeArray(0);
    shader_program->setAttributeBuffer(1, GL_FLOAT, texCoordOffset, 2);
    shader_program->enableAttributeArray(1);
    shader_program->setAttributeBuffer(2, GL_FLOAT, normalOffset, 3);
    shader_program->enableAttributeArray(2);

    glDrawElements(displayMode, m_numIndices, GL_UNSIGNED_INT, 0);   //mode count type indices
    //vbo.release();
    //ibo.release();
    //vao.release();
    //shader_program->release();
    if(displayMode == GL_TRIANGLES && texture != nullptr){
        texture->release();
    }
}
