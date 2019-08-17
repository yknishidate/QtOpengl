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
    for (int i = 0;i <= 20; i++) {
        grids.push_back(Vertex(QVector3D(  10.0f, 0.0f, i-10.0f)));
        grids.push_back(Vertex(QVector3D( -10.0f, 0.0f, i-10.0f)));
        grids.push_back(Vertex(QVector3D( i-10.0f, 0.0f,  10.0f)));
        grids.push_back(Vertex(QVector3D( i-10.0f, 0.0f, -10.0f)));
    }

    vbo.bind();
    vbo.allocate(&grids[0], grids.size() * sizeof(Vertex));
}


void Grid::draw(QOpenGLShaderProgram *shader_program){
    glLineWidth(0.6f);
    vbo.bind();

    int vertexLocation = shader_program->attributeLocation("position");
    shader_program->enableAttributeArray(vertexLocation);
    shader_program->setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3, sizeof(Vertex));
    glDrawArrays(GL_LINES, 0, 84);  //4*21
}
