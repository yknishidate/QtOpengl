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
#include "spheremodel.h"


class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = nullptr);
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    GLenum displayMode;

    QMatrix4x4 getViewMatrix(){return camera.matrix;}
    Camera* getCamera(){return &camera;}
    int getXRot(){return xRot;}
    int getYRot(){return yRot;}
    std::vector<Model *>* getModelsPtr(){return &models;}
    std::vector<Model *> getModels(){return models;}

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
    void createPrimitive(int type);
    void openTexture();
    void selectedModel(QModelIndex modelIndex);

    void createSphere(float r, int st, int sl);
    void changeSphere(float r, int st, int sl);
    void changeSphereRad(float r);
    void changeSphereSeg(int st);

    void changeMeterialType(int t);
    void setMaterialDiffColor(QColor color);
    void setMaterialSpecColor(QColor color);
    void setMaterialTransColor(QColor color);
    void setShininess(int shine);
    void setMaterialLightColor(QColor color);
    void setMaterialIor(double i);

    void deleteModel(int id);

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

    void setMeterialType(int type);

    void setColorButton(QColor color);
    void setColorButton_2(QColor color);
    void setTransColorButton(QColor color);
    void setLightColorButton(QColor color);
    void setShininessSlider(int shine);
    void setIorSpinBox(double i);

    void setTextureName(QString s);
    void setSphereRadSpinBox(double r);
    void setSphereSegSpinBox(int st);
    void sphereSelected(bool arg);
    void cubeSelected(bool arg);

    void setMeterialIor(float i);

private:
    int xRot;
    int yRot;
    int zRot;
    QPoint lastPos;

    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;

    Shader shader;

    QMatrix4x4 modelMatrix;
    QMatrix3x3 normalMatrix;
    QMatrix4x4 proj;

    Camera camera;
    Grid grid;

    std::vector<Model *> models;
    int modelCount = 0;

    bool culling;
    bool testing;

    int frame;
    int selectedModelIndex = -1;

    GLuint textureGL;

};

#endif // GLWIDGET_H
