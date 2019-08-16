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

    void open();

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
    Mesh *cube;
    Mesh *monkey;
    Mesh *chest;
    QVector<Mesh> *meshes;
    int meshCount = 0;
    Grid *grid;

    bool loaded = false;

    QOpenGLTexture *texture;

};

#endif // GLWIDGET_H
