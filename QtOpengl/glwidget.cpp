#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
{

}



void GLWidget::initializeGL()
{

    initializeOpenGLFunctions();
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    // Shader
    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl");

    m_program->link();
    m_program->bind();

    // Location
    m_projMatrixLoc = m_program->uniformLocation("projMatrix");
    m_mvMatrixLoc = m_program->uniformLocation("mvMatrix");
    //m_normalMatrixLoc = m_program->uniformLocation("normalMatrix");
    //m_lightPosLoc = m_program->uniformLocation("lightPos");

    // VBO
    m_vertex.create();
    m_vertex.bind();
    m_vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertex.allocate(m_vertices, sizeof(m_vertices));

    // VAO
    m_object.create();
    m_object.bind();
    m_program->enableAttributeArray(0);
    m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), 3, Vertex::stride());

    // Camera
    m_camera.setToIdentity();
    m_camera.translate(0, 0, -1);

    m_object.release();
    m_vertex.release();
    m_program->release();
}

void GLWidget::resizeGL(int w, int h)
{
    //単位行列に設定
    m_proj.setToIdentity();

    //透視投影にする行列をかける
    //Angle, AspectRatio, Near, Far
    m_proj.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

    m_world.setToIdentity();

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



QSize GLWidget::minimumSizeHint() const
{
    return QSize(400, 400);
}

QSize GLWidget::sizeHint() const
{
    return QSize(400, 400);
}

