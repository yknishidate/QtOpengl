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

    void changeModelPositionX(double x);
    void changeModelPositionY(double y);
    void changeModelPositionZ(double z);
    void changeModelScaleX(double x);
    void changeModelScaleY(double y);
    void changeModelScaleZ(double z);
    void changeModelRotationX(double x);
    void changeModelRotationY(double y);
    void changeModelRotationZ(double z);

    void open();
    void openTexture();
    void selectedModel(QModelIndex modelIndex);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);
    void loadedMesh(std::string name);
    void loadedModel(Model*);
    void loadedTexture(QString);

    void setSpinboxPositionX(double n);
    void setSpinboxPositionY(double n);
    void setSpinboxPositionZ(double n);
    void setSpinboxScaleX(double n);
    void setSpinboxScaleY(double n);
    void setSpinboxScaleZ(double n);
    void setSpinboxRotationX(double n);
    void setSpinboxRotationY(double n);
    void setSpinboxRotationZ(double n);

    void setTextureName(QString s);

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

    std::vector<Model *> models;
    int modelCount = 0;

    bool culling;
    bool testing;

    int frame;
    int selectedModelIndex = -1;

};

#endif // GLWIDGET_H
