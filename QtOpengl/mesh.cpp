#include "mesh.h"
#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QOpenGLExtraFunctions>


Mesh::Mesh()
    : ibo(QOpenGLBuffer::IndexBuffer)
{
}

Mesh::Mesh(const QString& fileName)
    : ibo(QOpenGLBuffer::IndexBuffer)
{
    initMesh(OBJModel(fileName.toStdString()).ToIndexedModel());
}

Mesh::~Mesh()
{
    vbo.destroy();
    ibo.destroy();
}

void Mesh::initMesh(const IndexedModel& model)
{
    qDebug() << "---initMesh()---";
    initializeOpenGLFunctions();

    positionOffset = 0;
    texCoordOffset = positionOffset + model.positions.size()*sizeof(model.positions[0]);
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

    qDebug() << "Points :" << model.positions.size();
    qDebug() << "Indeces:" << model.indices.size();
    qDebug() << "vboTotalSize  :" << vboTotalSize;
    qDebug() << "mesh's vbo ID:" << vbo.bufferId();
    qDebug() << "mesh's ibo ID:" << ibo.bufferId();
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
    shader_program->setAttributeBuffer(2, GL_FLOAT, normalOffset, 3);
    shader_program->enableAttributeArray(2);


    glDrawElements(displayMode, m_numIndices, GL_UNSIGNED_INT, 0);   //mode count type indices
    //vbo.release();
    //ibo.release();
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
    vbo.bind();
    vbo.allocate(vertices, sizeof(vertices));

    ibo.create();
    ibo.bind();
    ibo.allocate(indices, sizeof(indices));

    m_numIndices = sizeof(indices)/sizeof(indices[0]);

    qDebug() << "cube's vbo ID:" << vbo.bufferId();
    qDebug() << "cube's ibo ID:" << ibo.bufferId();
    vbo.release();
    ibo.release();
}



void Mesh::drawCube(QOpenGLShaderProgram *shader_program, GLenum displayMode)
{
    vbo.bind();
    ibo.bind();

    shader_program->enableAttributeArray(0);
    shader_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), 3, sizeof(Vertex));

    shader_program->enableAttributeArray(1);
    shader_program->setAttributeBuffer(1, GL_FLOAT, Vertex::texCoordOffset(), 2, sizeof(Vertex));
    vbo.release();
    ibo.release();

    // Draw using IBO
    glDrawElements(displayMode, m_numIndices, GL_UNSIGNED_SHORT, 0);

}

