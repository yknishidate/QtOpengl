#include "glwidget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWheelEvent>
#include <typeinfo>
#include <QtMath>


GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      displayMode(GL_TRIANGLES),
      xRot(20*16), yRot(-45*16), zRot(0),
      camera(QVector3D(0,0,20), QVector3D(0,0,0)),
      culling(false), testing(true)
{
}

void GLWidget::open(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Obj Files (*.obj);"));
    qDebug() << "---open()---";

    if(fileName != ""){
        models.push_back(new Model(fileName));
        emit loadedModel(models[modelCount]);
        modelCount++;
        update();
    }
}

void GLWidget::createPrimitive(int type){
    models.push_back(new Model(type));
    emit loadedModel(models[modelCount]);
    modelCount++;
    update();
}

// Sphere Prim
void GLWidget::createSphere(float r, int st, int sl){
    models.push_back(new SphereModel(r, st, sl));
    emit loadedModel(models[modelCount]);
    modelCount++;
    update();
}
void GLWidget::changeSphere(float r, int st, int sl){
    models[selectedModelIndex]->change(r, st, sl);
    models[selectedModelIndex]->setRadius(r);
    update();
}
void GLWidget::changeSphereRad(float r){
    models[selectedModelIndex]->change(r, models[selectedModelIndex]->getStacks(), models[selectedModelIndex]->getSlices());
    models[selectedModelIndex]->setRadius(r);
    update();
}
void GLWidget::changeSphereSeg(int st){
    models[selectedModelIndex]->change(models[selectedModelIndex]->getRadius(), st, st*2);
    models[selectedModelIndex]->setStacks(st);
    models[selectedModelIndex]->setSlices(st*2);
    update();
}

void GLWidget::openTexture(){
    QString fileName = QFileDialog::getOpenFileName(this);
    qDebug() << "---openTexture()---";
    if(fileName != "" && selectedModelIndex != -1){
        models[selectedModelIndex]->setTexture(fileName);
        emit loadedTexture(fileName);
        update();
    }
}

void GLWidget::selectedModel(QModelIndex modelIndex){
    selectedModelIndex = modelIndex.row();

    // Sphere Selected
    if(typeid(*models[selectedModelIndex]) == typeid(SphereModel)){
        emit sphereSelected(true);
        emit setSphereRadSpinBox(models[selectedModelIndex]->getRadius());
        emit setSphereSegSpinBox(models[selectedModelIndex]->getStacks());
    }else {
        emit sphereSelected(false);
    }

    // Set Coordinates Data to GUI
    emit setSpinboxPositionX(models[selectedModelIndex]->getPosition().x());
    emit setSpinboxPositionY(models[selectedModelIndex]->getPosition().y());
    emit setSpinboxPositionZ(models[selectedModelIndex]->getPosition().z());
    emit setSpinboxScaleX(   models[selectedModelIndex]->getScale().x());
    emit setSpinboxScaleY(   models[selectedModelIndex]->getScale().y());
    emit setSpinboxScaleZ(   models[selectedModelIndex]->getScale().z());
    emit setSpinboxRotationX(models[selectedModelIndex]->getRotation().x());
    emit setSpinboxRotationY(models[selectedModelIndex]->getRotation().y());
    emit setSpinboxRotationZ(models[selectedModelIndex]->getRotation().z());

    // Set Material Data to GUI
    emit setTextureName(         models[selectedModelIndex]->getTextureName());
    emit setMeterialType(        models[selectedModelIndex]->getMaterialType());
    emit setColorButton(         models[selectedModelIndex]->getMaterialDiffColor());
    emit setColorButton_2(       models[selectedModelIndex]->getMaterialSpecColor());
    emit setTransColorButton(    models[selectedModelIndex]->getMaterialTransColor());
    emit setLightColorButton(    models[selectedModelIndex]->getMaterialLightColor());
    emit setShininessSlider(sqrt(models[selectedModelIndex]->getShininess()));
    emit setIorSpinBox(          models[selectedModelIndex]->getMaterialIor());
}


void GLWidget::initializeGL(){
    initializeOpenGLFunctions();
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    qDebug() << "version:"      << QLatin1String(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    qDebug() << "GLSL version:" << QLatin1String(reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)));

    shader.init();
    grid.init();
    modelMatrix.setToIdentity();

    frame = 0;
}


void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);

    if(culling) glEnable(GL_CULL_FACE);
    else        glDisable(GL_CULL_FACE);
    if(testing) glEnable(GL_DEPTH_TEST);
    else        glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    camera.transform(xRot, yRot);

    modelMatrix.setToIdentity();
    shader.update(proj, camera.matrix);

    grid.draw(shader.program);

    // Draw Models
    for(int i = 0; i < modelCount; i++){
        modelMatrix.setToIdentity();
        modelMatrix.translate(models[i]->getPosition());
        modelMatrix.rotate(QQuaternion::fromEulerAngles(models[i]->getRotation()));
        modelMatrix.scale(models[i]->getScale());
        normalMatrix = modelMatrix.normalMatrix();

        shader.update(proj, camera.matrix, modelMatrix, normalMatrix);
        shader.program->setUniformValue("cameraPosition", camera.getCameraPos());
        models[i]->draw(shader.program, displayMode, false);

        // Draw Outline
        if(selectedModelIndex == i){
            glEnable(GL_CULL_FACE);
            glFrontFace(GL_CW);
            modelMatrix.scale(1.01);
            shader.update(proj, camera.matrix, modelMatrix, normalMatrix);
            if(displayMode == GL_TRIANGLES) models[i]->draw(shader.program, displayMode, true);
            glDisable(GL_CULL_FACE);
            glFrontFace(GL_CCW);
        }
    }
//    qDebug() << ++frame;
}


///////////////////////////////////////////////////////////////////////////////////


void GLWidget::resizeGL(int w, int h){
    proj.setToIdentity();
    proj.perspective(/* (atan(1/2)*2) = */ 53.13f, GLfloat(w)/h, 0.01f, 1000.0f);
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



// Slots = UI Changed
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

void GLWidget::changeMeterialType(int t){
    models[selectedModelIndex]->setMaterialType(t);
    update();
}
void GLWidget::setMaterialDiffColor(QColor color){
    models[selectedModelIndex]->setMaterialDiffColor(color);
    update();
}
void GLWidget::setMaterialSpecColor(QColor color){
    models[selectedModelIndex]->setMaterialSpecColor(color);
    update();
}
void GLWidget::setMaterialTransColor(QColor color){
    models[selectedModelIndex]->setMaterialTransColor(color);
    update();
}
void GLWidget::setMaterialLightColor(QColor color){
    models[selectedModelIndex]->setMaterialLightColor(color);
    update();
}

void GLWidget::setMaterialIor(double i){
    models[selectedModelIndex]->setMaterialIor(i);
    update();
}
void GLWidget::setShininess(int shine){
    models[selectedModelIndex]->setShininess(shine*shine);
    update();
}

void GLWidget::deleteModel(int id){
    qDebug() << models.size();
    models.erase(models.begin() + id);
    delete(*(models.begin() + id));
    qDebug() << models.size();
    modelCount--;
    update();
}

void GLWidget::changeModelPositionX(double x){models[selectedModelIndex]->setPositionX(x);update();}
void GLWidget::changeModelPositionY(double y){models[selectedModelIndex]->setPositionY(y);update();}
void GLWidget::changeModelPositionZ(double z){models[selectedModelIndex]->setPositionZ(z);update();}
void GLWidget::changeModelScaleX(double x){models[selectedModelIndex]->setScaleX(x);update();}
void GLWidget::changeModelScaleY(double y){models[selectedModelIndex]->setScaleY(y);update();}
void GLWidget::changeModelScaleZ(double z){models[selectedModelIndex]->setScaleZ(z);update();}
void GLWidget::changeModelRotationX(double x){models[selectedModelIndex]->setRotationX(x);update();}
void GLWidget::changeModelRotationY(double y){models[selectedModelIndex]->setRotationY(y);update();}
void GLWidget::changeModelRotationZ(double z){models[selectedModelIndex]->setRotationZ(z);update();}


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
