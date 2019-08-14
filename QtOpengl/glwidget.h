#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QVector3D>
#include <QtOpenGL>
#include <QMainWindow>
#include "mesh.h"
#include "grid.h"

/*
static const Vertex vertices[] = {
    Vertex( QVector3D( 0.0f,  0.0f, 0.0f), QVector3D( 0.0f,  0.0f, 0.0f)),
    Vertex( QVector3D( 2.0f,  0.0f, 0.0f), QVector3D( 1.0f,  0.0f, 0.0f)),
    Vertex( QVector3D( 0.0f,  2.0f, 0.0f), QVector3D( 0.0f,  0.0f, 0.0f)),

    Vertex( QVector3D( 0.0f,  0.0f, 0.0f), QVector3D( 0.0f,  0.0f, 0.0f)),
    Vertex( QVector3D( 0.0f,  0.0f, 2.0f), QVector3D( 0.0f,  1.0f, 0.0f)),
    Vertex( QVector3D( 2.0f,  0.0f, 0.0f), QVector3D( 0.0f,  0.0f, 0.0f)),

    Vertex( QVector3D( 0.0f,  0.0f, 0.0f), QVector3D( 0.0f,  0.0f, 0.0f)),
    Vertex( QVector3D( 0.0f,  2.0f, 0.0f), QVector3D( 0.0f,  0.0f, 1.0f)),
    Vertex( QVector3D( 0.0f,  0.0f, 2.0f), QVector3D( 0.0f,  0.0f, 0.0f)),
};

static const Vertex grids[] = {
    Vertex( QVector3D(  10000.0f, 0.0f, 0.0f), QVector3D( 0.5f,  0.2f, 0.2f)),
    Vertex( QVector3D( -10000.0f, 0.0f, 0.0f), QVector3D( 0.5f,  0.2f, 0.2f)),

    Vertex( QVector3D( 0.0f, 0.0f, -10000.0f), QVector3D( 0.5f,  0.2f, 0.2f)),
    Vertex( QVector3D( 0.0f, 0.0f,  10000.0f), QVector3D( 0.5f,  0.2f, 0.2f)),
};
*/



class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    GLWidget(QWidget *parent = nullptr);
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    GLenum displayMode;

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

    void setDisplayMode(bool arg);
    void setCullFace(bool arg);
    void setDepthTest(bool arg);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

private:
    void initShader();
    void initTextures();

    int xRot;
    int yRot;
    int zRot;
    QPoint lastPos;

    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;
    QOpenGLShaderProgram *shader_program;

    int projMatrixLoc;
    int mvMatrixLoc;
    int normalMatrixLoc;
    int lightPosLoc;

    QMatrix4x4 proj;
    QMatrix4x4 camera;
    QMatrix4x4 world;

    QVector3D cameraPos;
    QVector3D targetPos;
    bool culling;
    bool testing;

    Mesh *mesh;
    Grid *grid;
    QOpenGLTexture *texture;

};

#endif // GLWIDGET_H
