#ifndef MESH_H
#define MESH_H
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include "vertex.h"

enum MeshBufferPositions
{
    POSITION_VB,
    TEXCOORD_VB,
    NORMAL_VB,
    INDEX_VB
};

class Mesh : protected QOpenGLFunctions
{
public:
    Mesh();
    virtual ~Mesh();

    void drawCube(QOpenGLShaderProgram *shader_program, GLenum displayMode);

    void initCube();

private:
    QOpenGLBuffer vbo;
    QOpenGLBuffer ibo;
};

#endif // MESH_H
