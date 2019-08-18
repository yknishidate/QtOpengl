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
#include "camera.h"
#include "shader.h"
#include "texture.h"
#include "treeview.h"
#include "model.h"


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
    void openedMesh(std::string name);


private:
    int xRot;
    int yRot;
    int zRot;
    QPoint lastPos;

    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;

    Shader shader;

    QMatrix4x4 modelMatrix;
    QMatrix4x4 proj;

    Camera camera;
    Grid grid;


    // Mesh
    std::vector<Mesh *> meshesPtr;
    int meshCount = 0;

    std::vector<Model *> models;
    int modelCount = 0;

    bool culling;
    bool testing;

    int frame;

};

#endif // GLWIDGET_H
