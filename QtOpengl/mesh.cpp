#include "mesh.h"
#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QOpenGLExtraFunctions>


Mesh::Mesh()
    : ibo(QOpenGLBuffer::IndexBuffer)
{
}


Mesh::Mesh(Vertex* vertices, unsigned int numVertices, GLushort* indices, unsigned int numIndices)
{
    IndexedModel model;

    // "model"のメンバ変数（配列）に頂点情報を分けて詰める
    for(unsigned int i = 0; i < numVertices; i++)
    {
        model.positions.push_back(*vertices[i].GetPosition());
        model.texCoords.push_back(*vertices[i].GetTexCoord());
        model.normals.push_back(*vertices[i].GetNormal());
    }

    // "model"にIndex情報を詰める
    for(unsigned int i = 0; i < numIndices; i++){
        model.indices.push_back(indices[i]);
    }

    m_numIndices = numIndices;

    // "model"を"initMesh"に渡す
    initMesh(model);
}

Mesh::~Mesh()
{
    vbo.destroy();
    ibo.destroy();
}


void Mesh::initMesh(const IndexedModel& model)
{
    initializeOpenGLFunctions();

    positionOffset = 0;
    texCoordOffset = positionOffset + model.positions.size()*sizeof(model.positions[0]);
    normalOffset   = texCoordOffset + model.texCoords.size()*sizeof(model.texCoords[0]);
    vboTotalSize   = normalOffset   + model.normals.size()*sizeof(model.normals[0]);

    qDebug() << positionOffset << texCoordOffset << normalOffset << vboTotalSize;

    vbo.create();
    vbo.bind();
    vbo.allocate( &model.positions[0], vboTotalSize);        // "&qvec[0]" で渡す
    vbo.write( texCoordOffset, //offset
               &model.texCoords[0],                               //data
               model.texCoords.size()*sizeof(model.texCoords[0]));//size
    vbo.write( normalOffset, //offset
               &model.normals[0],                               //data
               model.normals.size()*sizeof(model.normals[0]));//size
    vbo.release();

    ibo.create();
    ibo.bind();
    ibo.allocate(&model.indices[0], model.indices.size() *sizeof(model.indices[0]));
    qDebug() <<model.indices.size()<<sizeof(model.indices[0]);

    //qDebug() << "model.positions.size()*sizeof(model.positions[0])" << model.positions.size()*sizeof(model.positions[0]);
    //qDebug() << "model.texCoords.size()*sizeof(model.texCoords[0])" << model.texCoords.size()*sizeof(model.texCoords[0]);
}


void Mesh::drawMesh(QOpenGLShaderProgram *shader_program, GLenum displayMode)
{
    //shader_program->bind();
    vao.bind();
    ibo.bind();
    vbo.bind();

    shader_program->setAttributeBuffer(0, GL_FLOAT, positionOffset, 3);  //stride = 0(default)
    shader_program->enableAttributeArray(0);
    shader_program->setAttributeBuffer(1, GL_FLOAT, texCoordOffset, 2);
    shader_program->enableAttributeArray(1);
    vbo.release();
    ibo.release();

    //glDrawArrays(GL_TRIANGLES, 0, 24);
    glDrawElements(GL_TRIANGLE_STRIP, m_numIndices, GL_UNSIGNED_SHORT, nullptr);   //mode count type indices
    //qDebug() << m_numIndices;

    //vao.release();
    //shader_program->release();
}







///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////







void Mesh::initCube()
{
    Vertex vertices[] = {
        // Vertex data for face 0
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.0f, 0.0f)},  // v0
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.0f)}, // v1
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.0f, 0.5f)},  // v2
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v3
        // Vertex data for face 1
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D( 0.0f, 0.5f)}, // v4
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.5f)}, // v5
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.0f, 1.0f)},  // v6
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v7
        // Vertex data for face 2
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v8
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(1.0f, 0.5f)},  // v9
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}, // v10
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(1.0f, 1.0f)},  // v11
        // Vertex data for face 3
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v12
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(1.0f, 0.0f)},  // v13
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v14
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(1.0f, 0.5f)},  // v15
        // Vertex data for face 4
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.0f)}, // v16
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v17
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v18
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v19
        // Vertex data for face 5
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v20
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v21
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v22
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}  // v23
    };

    GLushort indices[] = {
         0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
         4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
         8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
        20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    };

    initializeOpenGLFunctions();

    vbo.create();
    ibo.create();

    vbo.bind();
    vbo.allocate(vertices, sizeof(vertices));

    ibo.bind();
    ibo.allocate(indices, sizeof(indices));

    m_numIndices = sizeof(indices)/sizeof(indices[0]);
}



void Mesh::drawCube(QOpenGLShaderProgram *shader_program, GLenum displayMode)
{
    vbo.bind();
    ibo.bind();

    shader_program->enableAttributeArray(0);
    shader_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), 3, sizeof(Vertex));

    shader_program->enableAttributeArray(1);
    shader_program->setAttributeBuffer(1, GL_FLOAT, Vertex::texCoordOffset(), 2, sizeof(Vertex));

    // Draw using IBO
    glDrawElements(displayMode, m_numIndices, GL_UNSIGNED_SHORT, 0);
}

