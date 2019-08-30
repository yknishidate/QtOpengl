#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "glwidget.h"
#include <QtDebug>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Menu Bar
    connect(ui->actionOpen, SIGNAL(triggered()), ui->openGLWidget, SLOT(open()));

    // Tree View
    connect(ui->treeView, SIGNAL(clicked(QModelIndex)), ui->openGLWidget, SLOT(selectedModel(QModelIndex)));
    connect(ui->openGLWidget, SIGNAL(loadedModel(Model*)), ui->treeView, SLOT(addModel(Model*)));
    connect(ui->treeView, SIGNAL(modelDeleted(int)), ui->openGLWidget, SLOT(deleteModel(int)));

    // Attibute Group
    ui->attributesGroup->setVisible(false);
    connect(ui->treeView, SIGNAL(clicked(QModelIndex)), ui->attributesGroup, SLOT(setVisibleTrue(QModelIndex)));
    connect(ui->openGLWidget, SIGNAL(sphereSelected(bool)), ui->sphereWidget, SLOT(setVisible(bool)));
//    connect(ui->openGLWidget, SIGNAL(cubeSelected()), ui->sphereWidget, SLOT(setVisibleFalse()));


    // Coordinates
    // Spinbox -> Model
    connect(ui->doubleSpinBox_px, SIGNAL(valueChanged(double)), ui->openGLWidget, SLOT(changeModelPositionX(double)));
    connect(ui->doubleSpinBox_py, SIGNAL(valueChanged(double)), ui->openGLWidget, SLOT(changeModelPositionY(double)));
    connect(ui->doubleSpinBox_pz, SIGNAL(valueChanged(double)), ui->openGLWidget, SLOT(changeModelPositionZ(double)));
    connect(ui->doubleSpinBox_sx, SIGNAL(valueChanged(double)), ui->openGLWidget, SLOT(changeModelScaleX(double)));
    connect(ui->doubleSpinBox_sy, SIGNAL(valueChanged(double)), ui->openGLWidget, SLOT(changeModelScaleY(double)));
    connect(ui->doubleSpinBox_sz, SIGNAL(valueChanged(double)), ui->openGLWidget, SLOT(changeModelScaleZ(double)));
    connect(ui->doubleSpinBox_rx, SIGNAL(valueChanged(double)), ui->openGLWidget, SLOT(changeModelRotationX(double)));
    connect(ui->doubleSpinBox_ry, SIGNAL(valueChanged(double)), ui->openGLWidget, SLOT(changeModelRotationY(double)));
    connect(ui->doubleSpinBox_rz, SIGNAL(valueChanged(double)), ui->openGLWidget, SLOT(changeModelRotationZ(double)));
    // Model -> Spinbox
    connect(ui->openGLWidget, SIGNAL(setSpinboxPositionX(double)), ui->doubleSpinBox_px, SLOT(setValue(double)));
    connect(ui->openGLWidget, SIGNAL(setSpinboxPositionY(double)), ui->doubleSpinBox_py, SLOT(setValue(double)));
    connect(ui->openGLWidget, SIGNAL(setSpinboxPositionZ(double)), ui->doubleSpinBox_pz, SLOT(setValue(double)));
    connect(ui->openGLWidget, SIGNAL(setSpinboxScaleX(double)), ui->doubleSpinBox_sx, SLOT(setValue(double)));
    connect(ui->openGLWidget, SIGNAL(setSpinboxScaleY(double)), ui->doubleSpinBox_sy, SLOT(setValue(double)));
    connect(ui->openGLWidget, SIGNAL(setSpinboxScaleZ(double)), ui->doubleSpinBox_sz, SLOT(setValue(double)));
    connect(ui->openGLWidget, SIGNAL(setSpinboxRotationX(double)), ui->doubleSpinBox_rx, SLOT(setValue(double)));
    connect(ui->openGLWidget, SIGNAL(setSpinboxRotationY(double)), ui->doubleSpinBox_ry, SLOT(setValue(double)));
    connect(ui->openGLWidget, SIGNAL(setSpinboxRotationZ(double)), ui->doubleSpinBox_rz, SLOT(setValue(double)));


    // MaterialType
    connect(ui->openGLWidget, SIGNAL(setMeterialType(int)), ui->materialTypeComboBox, SLOT(setCurrentIndex(int)));
    connect(ui->materialTypeComboBox, SIGNAL(currentIndexChanged(int)), ui->openGLWidget, SLOT(changeMeterialType(int)));


    // Color
    QPalette pal = ui->colorButton->palette();
    pal.setColor(QPalette::Button, QColor(178.5f, 178.5f, 178.5f));
    ui->colorButton->setPalette(pal);
    connect(ui->openGLWidget, SIGNAL(setColorButton(QColor)), ui->colorButton, SLOT(setColor(QColor)));
    ui->colorButton_2->setPalette(pal);
    connect(ui->openGLWidget, SIGNAL(setColorButton_2(QColor)), ui->colorButton_2, SLOT(setColor(QColor)));
    ui->transColorButton->setPalette(pal);
    connect(ui->openGLWidget, SIGNAL(setTransColorButton(QColor)), ui->transColorButton, SLOT(setColor(QColor)));
    ui->lightColorButton->setPalette(pal);
    connect(ui->openGLWidget, SIGNAL(setLightColorButton(QColor)), ui->lightColorButton, SLOT(setColor(QColor)));


    // Texture
    connect(ui->toolButton, SIGNAL(clicked()), ui->openGLWidget, SLOT(openTexture()));
    connect(ui->openGLWidget, SIGNAL(loadedTexture(QString)), ui->lineEdit, SLOT(setText(QString)));
    ui->lineEdit->setReadOnly(true);
    connect(ui->openGLWidget, SIGNAL(setTextureName(QString)), ui->lineEdit, SLOT(setText(QString)));

    // Shine Slider
    connect(ui->shineSlider, SIGNAL(valueChanged(int)), ui->openGLWidget, SLOT(setShininess(int)));
    connect(ui->openGLWidget, SIGNAL(setShininessSlider(int)), ui->shineSlider, SLOT(setValue(int)));

    // Material Hide
    ui->label_11->hide();   ui->transColorButton->hide();
    ui->label_ior->hide();   ui->iorDoubleSpinBox->hide();
    ui->label_light->hide();ui->lightColorButton->hide();

    // Sphere
    connect(ui->openGLWidget, SIGNAL(setSphereRadSpinBox(double)), ui->radSpinBox, SLOT(setValue(double)));
    connect(ui->openGLWidget, SIGNAL(setSphereSegSpinBox(int)), ui->segBox, SLOT(setValue(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_colorButton_clicked()
{
    QColor chosenColor = QColorDialog::getColor();
    if(chosenColor.isValid()){
        QPalette pal = ui->colorButton->palette();
        pal.setColor(QPalette::Button, chosenColor);
        ui->colorButton->setPalette(pal);
        ui->colorButton->update();
        ui->openGLWidget->setMaterialDiffColor(chosenColor);
    }
}
void MainWindow::on_colorButton_2_clicked()
{
    QColor chosenColor = QColorDialog::getColor();
    if(chosenColor.isValid()){
        QPalette pal = ui->colorButton_2->palette();
        pal.setColor(QPalette::Button, chosenColor);
        ui->colorButton_2->setPalette(pal);
        ui->colorButton_2->update();
        ui->openGLWidget->setMaterialSpecColor(chosenColor);
    }
}

void MainWindow::on_transColorButton_clicked()
{
    QColor chosenColor = QColorDialog::getColor();
    if(chosenColor.isValid()){
        QPalette pal = ui->transColorButton->palette();
        pal.setColor(QPalette::Button, chosenColor);
        ui->transColorButton->setPalette(pal);
        ui->transColorButton->update();
        ui->openGLWidget->setMaterialTransColor(chosenColor);
    }
}

void MainWindow::on_lightColorButton_clicked()
{
    QColor chosenColor = QColorDialog::getColor();
    if(chosenColor.isValid()){
        QPalette pal = ui->lightColorButton->palette();
        pal.setColor(QPalette::Button, chosenColor);
        ui->lightColorButton->setPalette(pal);
        ui->lightColorButton->update();
        ui->openGLWidget->setMaterialLightColor(chosenColor);
    }
}



// Open Render Window
void MainWindow::on_actionRender_triggered()
{
    qDebug() << "---Render Triggered---";
    renderwindow = new RenderWindow(this,
                                    ui->openGLWidget->getXRot()/16.0f,
                                    ui->openGLWidget->getYRot()/16.0f,
                                    ui->openGLWidget->getCamera()->getLength(),
                                    ui->openGLWidget->getModels()
                                    );
    renderwindow->show();
}

// Create Primitives
void MainWindow::on_actionCube_triggered(){   ui->openGLWidget->createPrimitive(ModelType::CUBE); }
//void MainWindow::on_actionSphere_triggered(){ ui->openGLWidget->createPrimitive(ModelType::SPHERE); }
void MainWindow::on_actionSphere_triggered(){ui->openGLWidget->createSphere(5, 16, 32);}
void MainWindow::on_actionPlane_triggered(){  ui->openGLWidget->createPrimitive(ModelType::PLANE); }

// Options
void MainWindow::on_actionWireframe_toggled(bool arg1) { ui->openGLWidget->setDisplayMode(arg1);}
void MainWindow::on_actionBackface_Culling_toggled(bool arg1){ ui->openGLWidget->setCullFace(arg1);}
void MainWindow::on_actionDepth_Testing_toggled(bool arg1){ ui->openGLWidget->setDepthTest(arg1);}


void MainWindow::on_materialTypeComboBox_currentIndexChanged(int index)
{
    switch (index) {
    case 0: // Diff
        ui->label_7->show();    ui->colorButton->show();
        ui->label_8->show();    ui->colorButton_2->show();
        ui->label_11->hide();   ui->transColorButton->hide();
        ui->label_light->hide();ui->lightColorButton->hide();
        ui->label_ior->hide();  ui->iorDoubleSpinBox->hide();
        ui->label_9->show();    ui->shineSlider->show();
        ui->label_6->show();    ui->lineEdit->show();           ui->toolButton->show();
        break;
    case 1: // Metal
        ui->label_7->hide();    ui->colorButton->hide();
        ui->label_8->show();    ui->colorButton_2->show();
        ui->label_11->hide();   ui->transColorButton->hide();
        ui->label_light->hide();ui->lightColorButton->hide();
        ui->label_ior->hide();  ui->iorDoubleSpinBox->hide();
        ui->label_9->hide();    ui->shineSlider->hide();
        ui->label_6->hide();    ui->lineEdit->hide();           ui->toolButton->hide();
        break;
    case 2: // Glass
        ui->label_7->hide();    ui->colorButton->hide();
        ui->label_8->hide();    ui->colorButton_2->hide();
        ui->label_11->show();   ui->transColorButton->show();
        ui->label_light->hide();ui->lightColorButton->hide();
        ui->label_ior->show();  ui->iorDoubleSpinBox->show();
        ui->label_9->hide();    ui->shineSlider->hide();
        ui->label_6->hide();    ui->lineEdit->hide();           ui->toolButton->hide();
        break;
    case 3: // Light
        ui->label_7->hide();    ui->colorButton->hide();
        ui->label_8->hide();    ui->colorButton_2->hide();
        ui->label_11->hide();   ui->transColorButton->hide();
        ui->label_light->show();ui->lightColorButton->show();
        ui->label_ior->hide();  ui->iorDoubleSpinBox->hide();
        ui->label_9->hide();    ui->shineSlider->hide();
        ui->label_6->hide();    ui->lineEdit->hide();           ui->toolButton->hide();
        break;
    }
}


void MainWindow::on_radSpinBox_valueChanged(double arg1)
{
    ui->openGLWidget->changeSphereRad(arg1);
}

void MainWindow::on_segBox_valueChanged(int arg1)
{
    ui->openGLWidget->changeSphereSeg(arg1);
}
