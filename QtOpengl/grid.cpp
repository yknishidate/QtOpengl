#include "grid.h"
#include <QVector>
#include <QVector2D>
#include <QVector3D>

Grid::Grid()
{
}

Grid::~Grid()
{
    vbo.destroy();
}

void Grid::init(){
    initializeOpenGLFunctions();
    vbo.create();

    QVector<Vertex> grids;
    for (int i = 0;i <= 100; i++) {
        grids.push_back(Vertex(QVector3D(      500.0f, 0.0f, i*10-500.0f)));
        grids.push_back(Vertex(QVector3D(     -500.0f, 0.0f, i*10-500.0f)));
        grids.push_back(Vertex(QVector3D( i*10-500.0f, 0.0f,      500.0f)));
        grids.push_back(Vertex(QVector3D( i*10-500.0f, 0.0f,     -500.0f)));
    }

    vbo.bind();
    vbo.allocate(&grids[0], grids.size() * sizeof(Vertex));
}


void Grid::draw(QOpenGLShaderProgram *shader_program){
    shader_program->setUniformValue("textureSample", 0);
    shader_program->setUniformValue("wire", 1);
    glLineWidth(0.6f);
    vbo.bind();

    int vertexLocation = shader_program->attributeLocation("position");
    shader_program->enableAttributeArray(vertexLocation);
    shader_program->setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3, sizeof(Vertex));
    glDrawArrays(GL_LINES, 0, 404);  //4*(100+1)

}
