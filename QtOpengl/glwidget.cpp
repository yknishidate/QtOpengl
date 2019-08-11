#include "glwidget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>


GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      m_xRot(0),
      m_yRot(0),
      m_zRot(180*16),
      m_program(0),
      displayMode(GL_TRIANGLES)
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
    if (angle != m_xRot) {
        m_xRot = angle;
        emit xRotationChanged(angle);
        update();
    }
}
void GLWidget::setYRotation(int angle){
    qNormalizeAngle(angle);
    if (angle != m_yRot) {
        m_yRot = angle;
        emit yRotationChanged(angle);
        update();
    }
}
void GLWidget::setZRotation(int angle){
    qNormalizeAngle(angle);
    if (angle != m_zRot) {
        m_zRot = angle;
        emit zRotationChanged(angle);
        update();
    }
}

void GLWidget::initializeGL(){

    initializeOpenGLFunctions();
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    /* Shader */
    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl");
    m_program->link();
    m_program->bind();


    /* Location(頂点属性以外) */
    m_projMatrixLoc = m_program->uniformLocation("projMatrix");
    m_mvMatrixLoc = m_program->uniformLocation("mvMatrix");
    //m_normalMatrixLoc = m_program->uniformLocation("normalMatrix");
    //m_lightPosLoc = m_program->uniformLocation("lightPos");


    /* VBO */
    m_vertex.create();
    m_vertex.bind();
    m_vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
    /*スペースをバッファに割り当てる */
    m_vertex.allocate(m_vertices, sizeof(m_vertices));


    /* VAO */
    m_object.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_object);
    /* Location */
    m_program->enableAttributeArray(0);
    /* positionの配列を locarion = 0 にセットする */
    /* Location, Type, Offset, Stride */
    m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), 3, Vertex::stride());


    /* Camera */
    //m_camera.setToIdentity();
    //m_camera.translate(0, 0, -10);
    m_camera.lookAt(QVector3D(-2, 2, -5), QVector3D(0, 0.5f, 0), QVector3D(0, 1, 0));

    /* Light */
    //m_program->setUniformValue(m_lightPosLoc, QVector3D(0, 0, 70));

    m_object.release();
    m_vertex.release();
    m_program->release();
}


void GLWidget::setupVertexAttribs(){
    m_vertex.bind();
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glEnableVertexAttribArray(0);
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
    m_vertex.release();
}


void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

    m_world.setToIdentity();
    m_world.rotate(180.0f - (m_xRot / 16.0f), 1, 0, 0);
    m_world.rotate(m_yRot / 16.0f, 0, 1, 0);
    m_world.rotate(m_zRot / 16.0f, 0, 0, 1);

    //QOpenGLVertexArrayObject::Binderクラスを作成して、m_objectをバインドする
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_object);
    m_program->bind();
    m_program->setUniformValue(m_projMatrixLoc, m_proj);
    m_program->setUniformValue(m_mvMatrixLoc, m_camera * m_world);

    //Normal
    //QMatrix3x3 normalMatrix = m_world.normalMatrix();
    //m_program->setUniformValue(m_normalMatrixLoc, normalMatrix);

    QMatrix3x3 normalMatrix = m_world.normalMatrix();
    m_program->setUniformValue(m_normalMatrixLoc, normalMatrix);

    //m_object.bind();

    glDrawArrays(displayMode, 0, sizeof(m_vertices) / sizeof(m_vertices[0]));
    //glDrawArrays(GL_LINE_STRIP, 0, sizeof(m_vertices) / sizeof(m_vertices[0]));

    m_object.release();
    m_program->release();
}

void GLWidget::resizeGL(int w, int h){
    //単位行列に設定
    m_proj.setToIdentity();
    //透視投影にする行列をかける
    //Angle, AspectRatio, Near, Far
    m_proj.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
    qDebug()  << GLfloat(w) / h;
}


QSize GLWidget::minimumSizeHint() const{
    return QSize(400, 400);
}

QSize GLWidget::sizeHint() const{
    return QSize(400, 400);
}

void GLWidget::mousePressEvent(QMouseEvent *event){
    m_lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event){
    int dx = event->x() - m_lastPos.x();
    int dy = event->y() - m_lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(m_xRot + 4 * dy);
        setYRotation(m_yRot - 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        //setXRotation(m_xRot - 8 * dy);
        //setZRotation(m_zRot - 8 * dx);
    }
    m_lastPos = event->pos();
}

/*
void wheelEvent(QWheelEvent *event){
    //QPoint degress = event->angleDelta() / 8;
    //qDebug() << degress.rx() << "," << degress.ry();
}
*/

void GLWidget::setDisplayMode(bool arg){
    if(arg){
        displayMode = GL_LINE_STRIP;
    }else{
        displayMode = GL_TRIANGLES;
    }
    update();
}
