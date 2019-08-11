#include "glwidget.h"
#include <QtDebug>

GLWidget::GLWidget(QWidget *parent)
{

}



void GLWidget::initializeGL()
{

    initializeOpenGLFunctions();
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    /* Shader */
    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl");
    //m_program->bindAttributeLocation("vertex", 0);
    //m_program->bindAttributeLocation("normal", 1);
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
    //m_object.bind();
    /* Location */
    m_program->enableAttributeArray(0);
    /* positionの配列を locarion = 0 にセットする */
    /* Location, Type, Offset, Stride */
    m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), 3, Vertex::stride());


    //setupVertexAttribs();


    /* Camera */
    m_camera.setToIdentity();
    m_camera.translate(0, 0, -1);
    m_camera.lookAt(QVector3D(0, 0, -1), QVector3D(0,0,0), QVector3D(0, 1, 0));

    /* Light */
    //m_program->setUniformValue(m_lightPosLoc, QVector3D(0, 0, 70));

    m_object.release();
    m_vertex.release();
    m_program->release();
}

void GLWidget::setupVertexAttribs()
{
    m_vertex.bind();
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glEnableVertexAttribArray(0);
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
    m_vertex.release();
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

    m_world.setToIdentity();
    //m_world.rotate(180.0f - (m_xRot / 16.0f), 1, 0, 0);
    //m_world.rotate(m_yRot / 16.0f, 0, 1, 0);
    //m_world.rotate(m_zRot / 16.0f, 0, 0, 1);

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

    glDrawArrays(GL_TRIANGLES, 0, sizeof(m_vertices) / sizeof(m_vertices[0]));

    m_object.release();
    m_program->release();
}

void GLWidget::resizeGL(int w, int h)
{
    //単位行列に設定
    m_proj.setToIdentity();
    //透視投影にする行列をかける
    //Angle, AspectRatio, Near, Far
    m_proj.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
    qDebug()  << GLfloat(w) / h;
}


QSize GLWidget::minimumSizeHint() const
{
    return QSize(400, 400);
}

QSize GLWidget::sizeHint() const
{
    return QSize(400, 400);
}

