#ifndef MESH_H
#define MESH_H
#include <QtOpenGL>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QVector>
#include "vertex.h"



class IndexedModel
{
public:
    QVector<QVector3D> positions;
    QVector<QVector2D> texCoords;
    QVector<QVector3D> normals;
    QVector<GLushort> indices;

    void calcNormals();
};

class Mesh : protected QOpenGLFunctions, public QOpenGLWidget
{
public:
    Mesh();
    Mesh(Vertex* vertices, unsigned int numVertices, GLushort* indices, unsigned int numIndices);
    virtual ~Mesh();
    void initMesh(const IndexedModel& model);
    void drawMesh(QOpenGLShaderProgram *shader_program, GLenum displayMode);

    void drawCube(QOpenGLShaderProgram *shader_program, GLenum displayMode);
    void initCube();

private:
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer vbo;
    QOpenGLBuffer ibo;
    unsigned int m_numVertices;
    unsigned int m_numIndices;

    int positionOffset;
    int texCoordOffset;
    int normalOffset;
    int vboTotalSize;
};

#endif // MESH_H
