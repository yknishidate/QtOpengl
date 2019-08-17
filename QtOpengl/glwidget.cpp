#include "glwidget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWheelEvent>


GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      displayMode(GL_TRIANGLES),
      xRot(0), yRot(0), zRot(0),
      camera(QVector3D(2,2,5), QVector3D(0,1,0)),
      culling(false), testing(true)
{
}

void GLWidget::open(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Obj Files (*.obj);"));
    qDebug() << "---open()---";
    if(fileName != ""){
        qDebug() << "fileName:" << fileName;
        mesh = new Mesh(fileName);
        loaded = true;
        emit openedMesh(mesh->name);
    }else{
        qDebug() << "Don't Open File";
    }
}

void GLWidget::initializeGL(){
    initializeOpenGLFunctions();
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    shader.init();
    textures[0].init(QString("E:/3D Objects/assets/chest/diffuse.webp"));
    textures[1].init(QString("E:/3D Objects/assets/chest/cube.png"));
    textures[2].init(QString("E:/3D Objects/assets/chest/cube_blue.png"));

    grid.init();
}


void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);

    if(culling) glEnable(GL_CULL_FACE);
    else        glDisable(GL_CULL_FACE);
    if(testing) glEnable(GL_DEPTH_TEST);
    else        glDisable(GL_DEPTH_TEST);

    camera.transform(xRot, yRot);
    shader.update(proj, camera.matrix);

    //Draw Grid
    grid.draw(shader.program);

    // Draw Mesh
    if(loaded){
        mesh->draw(shader.program, displayMode, textures[0]);
    }
}



///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////


void GLWidget::resizeGL(int w, int h){
    proj.setToIdentity();
    proj.perspective(45.0f, GLfloat(w)/h, 0.01f, 1000.0f);
}


// Window Size
QSize GLWidget::minimumSizeHint() const{return QSize(600, 400);}
QSize GLWidget::sizeHint() const{return QSize(600, 400);}


// Mouse Event
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



/*----------Slots----------*/
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
        //emit xRotationChanged(angle);
        update();
    }
}
void GLWidget::setYRotation(int angle){
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        //emit yRotationChanged(angle);
        update();
    }
}
void GLWidget::setZRotation(int angle){
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        //emit zRotationChanged(angle);
        update();
    }
}
