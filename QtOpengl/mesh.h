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
    Mesh(const QString& fileName);
    Mesh(Vertex* vertices, unsigned int numVertices, GLuint* indices, unsigned int numIndices);
    virtual ~Mesh();

    //Mesh& operator=(const Mesh& ms);

    void initMesh(const IndexedModel& model);
    void drawMesh(QOpenGLShaderProgram *shader_program, GLenum displayMode);

    void drawCube(QOpenGLShaderProgram *shader_program, GLenum displayMode);
    void initCube();

    void loadMesh(const QString& fileName);

    //bool isInitialized = false;

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
