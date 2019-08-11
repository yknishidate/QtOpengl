#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QVector3D>
#include <QtOpenGL>
#include <QMainWindow>
#include <QWheelEvent>
#include "vertex.h"

/* Triangel */
/*static const Vertex m_vertices[] = {
    Vertex( QVector3D( 0.0f,  2.0f, 0.0f)),
    Vertex( QVector3D( 2.0f,  0.0f, 0.0f)),
    Vertex( QVector3D( 0.0f,  0.0f, 0.0f)),
};
*/

/* Axis */
/*static const Vertex m_vertices[] = {
    Vertex( QVector3D( 2.0f,  0.0f, 0.0f)),
    Vertex( QVector3D( 0.0f,  0.0f, 0.0f)),

    Vertex( QVector3D( 0.0f,  2.0f, 0.0f)),
    Vertex( QVector3D( 0.0f,  0.0f, 0.0f)),

    Vertex( QVector3D( 0.0f,  0.0f, 2.0f)),
    Vertex( QVector3D( 0.0f,  0.0f, 0.0f)),
};
*/

static const Vertex m_vertices[] = {

    Vertex( QVector3D( 0.0f,  0.0f, 0.0f)),
    Vertex( QVector3D( 2.0f,  0.0f, 0.0f)),
    Vertex( QVector3D( 0.0f,  2.0f, 0.0f)),

    Vertex( QVector3D( 0.0f,  0.0f, 0.0f)),
    Vertex( QVector3D( 0.0f,  0.0f, 2.0f)),
    Vertex( QVector3D( 2.0f,  0.0f, 0.0f)),

    Vertex( QVector3D( 0.0f,  0.0f, 0.0f)),
    Vertex( QVector3D( 0.0f,  2.0f, 0.0f)),
    Vertex( QVector3D( 0.0f,  0.0f, 2.0f)),
};


class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    GLenum displayMode;

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    //void wheelEvent(QWheelEvent *event) override;

    //void initTextures();


public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void setDisplayMode(bool arg);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

private:
    void setupVertexAttribs();

    int m_xRot;
    int m_yRot;
    int m_zRot;
    QPoint m_lastPos;

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
