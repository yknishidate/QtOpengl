#ifndef GRID_H
#define GRID_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include "vertex.h"

class Grid : protected QOpenGLFunctions{
public:
    Grid();
    virtual ~Grid();
    void draw(QOpenGLShaderProgram *shader_program);
    void init();

private:
    QOpenGLBuffer vbo;
};

#endif // GRID_H
