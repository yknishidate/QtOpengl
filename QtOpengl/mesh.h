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
#include "objloader.h"





class Mesh : protected QOpenGLFunctions, public QOpenGLWidget
{
public:
    Mesh();
    Mesh(const std::string& fileName);
    Mesh(Vertex* vertices, unsigned int numVertices, GLuint* indices, unsigned int numIndices);
    virtual ~Mesh();
    void initMesh(const IndexedModel& model);
    void drawMesh(QOpenGLShaderProgram *shader_program, GLenum displayMode);

    void drawCube(QOpenGLShaderProgram *shader_program, GLenum displayMode);
    void initCube();

private:
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer vbo;
    QOpenGLBuffer ibo;
    GLuint m_numVertices;
    GLuint m_numIndices;

    int positionOffset;
    int texCoordOffset;
    int normalOffset;
    int vboTotalSize;
};

#endif // MESH_H
