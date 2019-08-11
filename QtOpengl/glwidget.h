#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QVector3D>
#include <QtOpenGL>
#include "vertex.h"

static const Vertex m_vertices[] = {
    Vertex( QVector3D( 0.0f,  0.5f, 1.0f)),
    Vertex( QVector3D( 0.5f, -0.5f, 1.0f)),
    Vertex( QVector3D(-0.5f, -0.5f, 1.0f)),
};


class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void initTextures();

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;


private:
    QOpenGLBuffer m_vertex;
    QOpenGLVertexArrayObject m_object;
    QOpenGLShaderProgram *m_program;

    int m_projMatrixLoc;
    int m_mvMatrixLoc;
    int m_normalMatrixLoc;
    int m_lightPosLoc;

    QMatrix4x4 m_proj;
    QMatrix4x4 m_camera;
    QMatrix4x4 m_world;

};

#endif // GLWIDGET_H
