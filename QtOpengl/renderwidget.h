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

class RenderWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_3_Core
{
    Q_OBJECT

    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer *m_vertexBuffer;
    QOpenGLBuffer *m_indexBuffer;
    QOpenGLShaderProgram *m_computeProgram;
    QOpenGLShaderProgram *m_renderProgram;
    QOpenGLShader *m_computeShader;
    QOpenGLShader *m_fragmentShader;
    QOpenGLShader *m_vertexShader;
    QOpenGLTexture *m_tex_output;
    QOpenGLTexture *m_tex_input;
    QOpenGLTexture *m_hdri;


public:
    RenderWidget(QWidget *parent = nullptr);
    ~RenderWidget();
    void setXRot(float x){xRot = x;}
    void setYRot(float y){yRot = y;}

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

private:
    unsigned accumN = 1;
    GLuint accum;
    int frame = 0;
    const int tex_w = 960, tex_h = 540;
    GLuint tex_input;
    GLuint tex_output;

    bool rendering = true;

    float xRot;
    float yRot;

public slots:
    void stopRendering();

};

#endif // RENDERWIDGET_H
