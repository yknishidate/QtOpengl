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

enum ModelType{
    POLYGONMODEL = 0,
    PLANE        = 1,
    CUBE         = 2,
    SPHERE       = 3
};

class Mesh : protected QOpenGLFunctions{
public:
    Mesh();
    Mesh(const QString& fileName);
    Mesh(const int type);
    virtual ~Mesh();

    std::string getName(){return name;}

    void createSphere(float radius, int stacks, int slices);
    void changeSphere(float radius, int stacks, int slices);

    void init(const IndexedModel& model);
    void change(const IndexedModel& model);
    void draw(QOpenGLShaderProgram *shader_program, GLenum displayMode, QOpenGLTexture *texture,int materialType);
    void initCubeMap();

private:
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer vbo;
    QOpenGLBuffer ibo;
    GLuint m_numVertices;
    GLuint m_numIndices;

    IndexedModel indexModel;

    GLuint textureGL;

    std::string name;

    int texCoordOffset;
    int normalOffset;
    int vboTotalSize;

};

#endif // MESH_H
