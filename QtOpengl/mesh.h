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
#include "texture.h"





class Mesh : protected QOpenGLFunctions, public QOpenGLWidget
{
public:
    Mesh();
    Mesh(const QString& fileName);
    virtual ~Mesh();

    std::string name;

    void init(const IndexedModel& model);
    void draw(QOpenGLShaderProgram *shader_program, GLenum displayMode, Texture texture);

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
