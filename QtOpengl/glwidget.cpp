#include "glwidget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWheelEvent>


GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      displayMode(GL_TRIANGLE_STRIP),
      xRot(0), yRot(0), zRot(0),
      shader_program(nullptr),
      cameraPos(2, 2, 5), targetPos(0, 0.5f, 0),
      culling(false), testing(true),
      mesh(0),
      texture(0)
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

    initShader();
    initTextures();

    mesh = new Mesh();
    mesh->initCube();

    /* Light */
    //shader_program->setUniformValue(lightPosLoc, QVector3D(0, 0, 70));

    glLineWidth(1.5f);
}


void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);

    texture->bind();

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
    camera.lookAt(cameraPos * world, targetPos, QVector3D(0, 1, 0));

    /* Shader */
    shader_program->bind();
    shader_program->setUniformValue(projMatrixLoc, proj);
    shader_program->setUniformValue(mvMatrixLoc, camera);

    shader_program->setUniformValue("texture", 0);

    mesh->drawCube(shader_program, displayMode);

    //vbo.bind();
    //vbo.allocate(vertices, sizeof(vertices));
    //glDrawArrays(displayMode, 0, sizeof(vertices) / sizeof(vertices[0]));


    /* Normal */
    //QMatrix3x3 normalMatrix = world.normalMatrix();
    //shader_program->setUniformValue(normalMatrixLoc, normalMatrix);

    /* Grid */
    //vbo.bind();
    //vbo.allocate(grids, sizeof(grids));
    //glDrawArrays(GL_LINES, 0, sizeof(grids) / sizeof(grids[0]));

    //shader_program->release();
}

void GLWidget::resizeGL(int w, int h){
    proj.setToIdentity();    //単位行列にする
    proj.perspective(45.0f, GLfloat(w)/h, 0.01f, 1000.0f);    //投影変換
}


/* Window Size */
QSize GLWidget::minimumSizeHint() const{return QSize(600, 400);}
QSize GLWidget::sizeHint() const{return QSize(600, 400);}


/* Mouse */
void GLWidget::mousePressEvent(QMouseEvent *event){
    lastPos = event->pos();
}
void GLWidget::mouseMoveEvent(QMouseEvent *event){
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();
    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 4 * dy);
        setYRotation(yRot + 4 * dx);
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
    else{displayMode = GL_TRIANGLE_STRIP;}
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

/* VBO */
void GLWidget::initVBO() {
    vbo.create();
    vbo.bind();
    //vbo.allocate(vertices, sizeof(vertices));

    /* position */
    shader_program->enableAttributeArray(0);
    //shader_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), 3, Vertex::stride());

    /* color */
    shader_program->enableAttributeArray(1);
    //shader_program->setAttributeBuffer(1, GL_FLOAT, Vertex::colorOffset(), 3, Vertex::stride());
    vbo.release();
}

/* Shader */
void GLWidget::initShader(){
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

    //shader_program->release();
}


void GLWidget::initTextures()
{
    // Load cube.png image
    texture = new QOpenGLTexture(QImage(":/cube.png").mirrored());

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
}
