#include "glwidget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWheelEvent>


GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      displayMode(GL_TRIANGLE_STRIP),
      xRot(0), yRot(0), zRot(0),
      shader_program(nullptr),
      cameraPos(2, 2, 5), targetPos(0, 0, 0),
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

    initShader();
    initTextures();


    Vertex vertices[] =    {
        Vertex(QVector3D(-1, -1, -1), QVector2D(1, 0), QVector3D(0, 0, -1)),
        Vertex(QVector3D(-1, 1, -1),  QVector2D(0, 0), QVector3D(0, 0, -1)),
        Vertex(QVector3D(1, 1, -1),   QVector2D(0, 1), QVector3D(0, 0, -1)),
        Vertex(QVector3D(1, -1, -1),  QVector2D(1, 1), QVector3D(0, 0, -1)),

        Vertex(QVector3D(-1, -1, 1),  QVector2D(1, 0), QVector3D(0, 0, 1)),
        Vertex(QVector3D(-1, 1, 1),   QVector2D(0, 0), QVector3D(0, 0, 1)),
        Vertex(QVector3D(1, 1, 1),    QVector2D(0, 1), QVector3D(0, 0, 1)),
        Vertex(QVector3D(1, -1, 1),   QVector2D(1, 1), QVector3D(0, 0, 1)),

        Vertex(QVector3D(-1, -1, -1), QVector2D(0, 1), QVector3D(0, -1, 0)),
        Vertex(QVector3D(-1, -1, 1),  QVector2D(1, 1), QVector3D(0, -1, 0)),
        Vertex(QVector3D(1, -1, 1),   QVector2D(1, 0), QVector3D(0, -1, 0)),
        Vertex(QVector3D(1, -1, -1),  QVector2D(0, 0), QVector3D(0, -1, 0)),

        Vertex(QVector3D(-1, 1, -1),  QVector2D(0, 1), QVector3D(0, 1, 0)),
        Vertex(QVector3D(-1, 1, 1),   QVector2D(1, 1), QVector3D(0, 1, 0)),
        Vertex(QVector3D(1, 1, 1),    QVector2D(1, 0), QVector3D(0, 1, 0)),
        Vertex(QVector3D(1, 1, -1),   QVector2D(0, 0), QVector3D(0, 1, 0)),

        Vertex(QVector3D(-1, -1, -1), QVector2D(1, 1), QVector3D(-1, 0, 0)),
        Vertex(QVector3D(-1, -1, 1),  QVector2D(1, 0), QVector3D(-1, 0, 0)),
        Vertex(QVector3D(-1, 1, 1),   QVector2D(0, 0), QVector3D(-1, 0, 0)),
        Vertex(QVector3D(-1, 1, -1),  QVector2D(0, 1), QVector3D(-1, 0, 0)),

        Vertex(QVector3D(1, -1, -1),  QVector2D(1, 1), QVector3D(1, 0, 0)),
        Vertex(QVector3D(1, -1, 1),   QVector2D(1, 0), QVector3D(1, 0, 0)),
        Vertex(QVector3D(1, 1, 1),    QVector2D(0, 0), QVector3D(1, 0, 0)),
        Vertex(QVector3D(1, 1, -1),   QVector2D(0, 1), QVector3D(1, 0, 0)),
    };

    GLushort indices[] = { 0,  1,  2,   0,  2,  3,      6,  5,  4,   7,  6,  4,
                          10,  9,  8,  11, 10,  8,     12, 13, 14,  12, 14, 15,
                          16, 17, 18,  16, 18, 19,     22, 21, 20,  23, 22, 20 };
    /*
    Vertex vertices[] = {
        // Vertex data for face 0
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.0f, 0.0f)},  // v0
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.0f)}, // v1
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.0f, 0.5f)},  // v2
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v3
        // Vertex data for face 1
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D( 0.0f, 0.5f)}, // v4
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.5f)}, // v5
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.0f, 1.0f)},  // v6
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v7
        // Vertex data for face 2
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v8
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(1.0f, 0.5f)},  // v9
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}, // v10
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(1.0f, 1.0f)},  // v11
        // Vertex data for face 3
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v12
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(1.0f, 0.0f)},  // v13
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v14
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(1.0f, 0.5f)},  // v15
        // Vertex data for face 4
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.0f)}, // v16
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v17
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v18
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v19
        // Vertex data for face 5
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v20
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v21
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v22
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}  // v23
    };

    GLushort indices[] = {
         0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
         4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
         8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
        20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    };
    */

    mesh = new Mesh(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));


    // Cube
    cube = new Mesh();
    cube->initCube();
    //Grid
    grid = new Grid();
    grid->initGrid();

    // Light
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

    // Rotate
    world.setToIdentity();
    world.rotate(xRot / 16.0f, 1, 0, 0);
    world.rotate(yRot / 16.0f, 0, 1, 0);

    // Camera Dolly
    camera.setToIdentity();
    camera.lookAt(cameraPos * world, targetPos, QVector3D(0, 1, 0));

    // Shader
    shader_program->bind();
    shader_program->setUniformValue(projMatrixLoc, proj);
    shader_program->setUniformValue(mvMatrixLoc, camera);


    // Draw
    mesh->drawMesh(shader_program, GL_TRIANGLES);
    //cube->drawCube(shader_program, displayMode);
    grid->drawGrid(shader_program);

    // Normal
    //QMatrix3x3 normalMatrix = world.normalMatrix();
    //shader_program->setUniformValue(normalMatrixLoc, normalMatrix);
}





///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////


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
    shader_program->setUniformValue("texture", 0);
    //normalMatrixLoc = shader_program->uniformLocation("normalMatrix");
    //lightPosLoc = shader_program->uniformLocation("lightPos");
}


void GLWidget::initTextures()
{
    // Load Texture
    texture = new QOpenGLTexture(QImage(":/resource/cube_blue.png").mirrored());
    // Minification -> Nearest
    texture->setMinificationFilter(QOpenGLTexture::Nearest);
    // Magnification -> Linear
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    // Repeat
    texture->setWrapMode(QOpenGLTexture::Repeat);
}


