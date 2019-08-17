#include "glwidget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWheelEvent>


GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      displayMode(GL_TRIANGLES),
      xRot(0), yRot(0), zRot(0),
      camera(QVector3D(2,2,5), QVector3D(0,1,0)),
      culling(false), testing(true),
      shader()
{
}

void GLWidget::initializeGL(){
    initializeOpenGLFunctions();
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    shader.init();
    initTextures();

    grid = new Grid();

    glLineWidth(1.5f);
}


void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);

    texture->bind();

    if(culling) glEnable(GL_CULL_FACE);
    else        glDisable(GL_CULL_FACE);
    if(testing) glEnable(GL_DEPTH_TEST);
    else        glDisable(GL_DEPTH_TEST);

    camera.transform(xRot, yRot);
    shader.update(proj, camera.matrix);

    // Draw
    if(loaded){
        mesh->drawMesh(shader.program, displayMode);
    }
    grid->drawGrid(shader.program);

    // Normal
    //QMatrix3x3 normalMatrix = world.normalMatrix();
    //shader_program->setUniformValue(normalMatrixLoc, normalMatrix);
}



///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

// Open
void GLWidget::open(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Obj Files (*.obj);"));
    qDebug() << "fileName:" << fileName;
    mesh = new Mesh(fileName);
    loaded = true;
}

void GLWidget::resizeGL(int w, int h){
    proj.setToIdentity();    //単位行列にする
    proj.perspective(45.0f, GLfloat(w)/h, 0.01f, 1000.0f);    //投影変換
}


// Window Size
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
    camera.dolly(degree);
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


void GLWidget::initTextures()
{
    // Load Texture
    texture = new QOpenGLTexture(QImage("C:/Qt/Qt5.13.0/Examples/Qt-5.13.0/qt3d/exampleresources/assets/chest/diffuse.webp").mirrored());
    // Minification -> Nearest
    texture->setMinificationFilter(QOpenGLTexture::Nearest);
    // Magnification -> Linear
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    // Repeat
    texture->setWrapMode(QOpenGLTexture::Repeat);
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

