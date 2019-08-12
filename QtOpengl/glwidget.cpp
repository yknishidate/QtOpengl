#include "glwidget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <QWheelEvent>


GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      displayMode(GL_TRIANGLES),
      xRot(0), yRot(0), zRot(0),
      shader_program(nullptr),
      cameraPos(2, 2, 5), targetPos(0, 0.5f, 0),
      culling(false), testing(true)
{
}

static void qNormalizeAngle(int &angle){
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}
void GLWidget::setXRotation(int angle){
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        update();
    }
}
void GLWidget::setYRotation(int angle){
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        update();
    }
}
void GLWidget::setZRotation(int angle){
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        update();
    }
}

void GLWidget::initializeGL(){
    initializeOpenGLFunctions();
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    /* Shader */
    shader_program = new QOpenGLShaderProgram();
    shader_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl");
    shader_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl");
    shader_program->link();
    shader_program->bind();

    /* Get Location from Shader */
    projMatrixLoc = shader_program->uniformLocation("projMatrix");
    mvMatrixLoc = shader_program->uniformLocation("mvMatrix");
    //normalMatrixLoc = shader_program->uniformLocation("normalMatrix");
    //lightPosLoc = shader_program->uniformLocation("lightPos");

    /* VBO */
    vbo.create();
    vbo.bind();
    vbo.allocate(vertices, sizeof(vertices));


    /* VAO */
    vao.create();
    vao.bind();
    shader_program->enableAttributeArray(0);                                                         /* positionを locarion = 0 にセット */
    shader_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), 3, Vertex::stride());  /* Location, Type, Offset, Stride  */

    /* Camera */
    camera.lookAt(cameraPos, targetPos, QVector3D(0, 1, 0));

    /* Light */
    //shader_program->setUniformValue(lightPosLoc, QVector3D(0, 0, 70));

    vao.release();
    vbo.release();
    shader_program->release();


    ///////////////////
    geometries = new GeometryEngine;
}


void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);

    if(culling) glEnable(GL_CULL_FACE);
    else        glDisable(GL_CULL_FACE);
    if(testing) glEnable(GL_DEPTH_TEST);
    else        glDisable(GL_DEPTH_TEST);

    /* Rotate */
    world.setToIdentity();
    world.rotate(xRot / 16.0f, 1, 0, 0);
    world.rotate(yRot / 16.0f, 0, 1, 0);

    /* Camera Dolly */
    camera.setToIdentity();
    camera.lookAt(cameraPos, targetPos, QVector3D(0, 1, 0));

    vbo.bind();
    vbo.allocate(vertices, sizeof(vertices));
    glLineWidth(1.0f);

    vao.bind();
    shader_program->bind();
    shader_program->setUniformValue(projMatrixLoc, proj);
    shader_program->setUniformValue(mvMatrixLoc, camera * world);
    /* Normal */
    //QMatrix3x3 normalMatrix = world.normalMatrix();
    //shader_program->setUniformValue(normalMatrixLoc, normalMatrix);
    glDrawArrays(displayMode, 0, sizeof(vertices) / sizeof(vertices[0]));


    /* Grid */
    vbo.bind();
    vbo.allocate(grids, sizeof(grids));
    glLineWidth(1.5f);
    shader_program->setUniformValue(mvMatrixLoc, camera);
    glDrawArrays(GL_LINES, 0, sizeof(grids) / sizeof(grids[0]));


    ///////////////////
    geometries->drawCubeGeometry(shader_program);
    ///////////////////


    vao.release();
    shader_program->release();
}

void GLWidget::resizeGL(int w, int h){
    proj.setToIdentity();    //単位行列にする
    proj.perspective(45.0f, GLfloat(w)/h, 0.01f, 1000.0f);    //投影変換
}


/* Window Size */
QSize GLWidget::minimumSizeHint() const{return QSize(400, 400);}
QSize GLWidget::sizeHint() const{return QSize(400, 400);}


/* Mouse */
void GLWidget::mousePressEvent(QMouseEvent *event){
    lastPos = event->pos();
}
void GLWidget::mouseMoveEvent(QMouseEvent *event){
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();
    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 4 * dy);
        setYRotation(yRot + 8 * dx);
    }
    lastPos = event->pos();
}
void GLWidget::wheelEvent(QWheelEvent *event){
    int degree = event->angleDelta().y() / 8;
    QVector3D relativeVec = targetPos - cameraPos;
    QVector3D cameraDir = relativeVec.normalized();
    if(relativeVec.length() > 2 || degree < 0){
        cameraPos = cameraPos + cameraDir * degree/10;
    }
    update();
}


/* Checkbox */
void GLWidget::setDisplayMode(bool arg){
    if(arg){displayMode = GL_LINE_STRIP;}
    else{displayMode = GL_TRIANGLES;}
    update();
}
void GLWidget::setCullFace(bool arg){
    culling = arg;
    update();
}
void GLWidget::setDepthTest(bool arg){
    testing = arg;
    update();
}


/*
void GLWidget::setupVertexAttribs(){
    vbo.bind();
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glEnableVertexAttribArray(0);
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
    vbo.release();
}
*/
