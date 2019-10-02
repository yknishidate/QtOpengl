#ifndef RENDERWIDGET_H
#define RENDERWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLBuffer>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>
#include <QDir>
#include "camera.h"
#include "model.h"

class RenderWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_3_Core{
    Q_OBJECT

    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer *m_vertexBuffer;
    QOpenGLBuffer *m_indexBuffer;
    QOpenGLShaderProgram *m_computeProgram;
    QOpenGLShaderProgram *m_renderProgram;
    QOpenGLShader *m_computeShader;
    QOpenGLShader *m_fragmentShader;
    QOpenGLShader *m_vertexShader;

    QGLFramebufferObject *catchFbo; //test

    GLuint tex_input;
    GLuint tex_output;

public:
    RenderWidget(QWidget *parent = nullptr);
    ~RenderWidget();
    void setXRot(float x){xRot = x;}
    void setYRot(float y){yRot = y;}
    void setCameraDistance(float l){cameraDistance = l;}
    void setModels(std::vector<Model *> m){models = m;}
    void changeRenderMode(const int mode);
    void saveImage();
    void changeDof(const bool checked);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

private:
    unsigned accumN = 1;
    GLuint accum;

    int frame = 0;
    const int tex_w = 960, tex_h = 540;
    bool rendering = true;
    float xRot;
    float yRot;
    float cameraDistance;

    int RenderMode = 0;
    bool Dof = 0;
    int PassLimit = 100;

    std::vector<Model *> models;

    bool save = false;

public slots:
    void stopRendering();
    void startRendering();

};

#endif // RENDERWIDGET_H
