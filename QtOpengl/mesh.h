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


class Mesh : protected QOpenGLFunctions
{
public:
    Mesh();
    Mesh(const QString& fileName);
    Mesh(const int type);
    virtual ~Mesh();

    std::string getName(){return name;}

    void init(const IndexedModel& model);
    void draw(QOpenGLShaderProgram *shader_program, GLenum displayMode, QOpenGLTexture *texture);

private:
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer vbo;
    QOpenGLBuffer ibo;
    GLuint m_numVertices;
    GLuint m_numIndices;

    std::string name;

    int texCoordOffset;
    int normalOffset;
    int vboTotalSize;

};

#endif // MESH_H
