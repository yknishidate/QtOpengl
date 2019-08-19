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
    connect(ui->checkBox, SIGNAL(toggled(bool)), ui->openGLWidget, SLOT(setDisplayMode(bool)));
    connect(ui->checkBox_2, SIGNAL(toggled(bool)), ui->openGLWidget, SLOT(setCullFace(bool)));
    connect(ui->checkBox_3, SIGNAL(toggled(bool)), ui->openGLWidget, SLOT(setDepthTest(bool)));
    connect(ui->actionOpen, SIGNAL(triggered()), ui->openGLWidget, SLOT(open()));

    //Spinbox -> Model
    connect(ui->doubleSpinBox_px, SIGNAL(valueChanged(double)), ui->openGLWidget, SLOT(changeModelPositionX(double)));
    connect(ui->doubleSpinBox_py, SIGNAL(valueChanged(double)), ui->openGLWidget, SLOT(changeModelPositionY(double)));
    connect(ui->doubleSpinBox_pz, SIGNAL(valueChanged(double)), ui->openGLWidget, SLOT(changeModelPositionZ(double)));
    connect(ui->doubleSpinBox_sx, SIGNAL(valueChanged(double)), ui->openGLWidget, SLOT(changeModelScaleX(double)));
    connect(ui->doubleSpinBox_sy, SIGNAL(valueChanged(double)), ui->openGLWidget, SLOT(changeModelScaleY(double)));
    connect(ui->doubleSpinBox_sz, SIGNAL(valueChanged(double)), ui->openGLWidget, SLOT(changeModelScaleZ(double)));
    connect(ui->doubleSpinBox_rx, SIGNAL(valueChanged(double)), ui->openGLWidget, SLOT(changeModelRotationX(double)));
    connect(ui->doubleSpinBox_ry, SIGNAL(valueChanged(double)), ui->openGLWidget, SLOT(changeModelRotationY(double)));
    connect(ui->doubleSpinBox_rz, SIGNAL(valueChanged(double)), ui->openGLWidget, SLOT(changeModelRotationZ(double)));

    //Model -> Spinbox
    connect(ui->openGLWidget, SIGNAL(setSpinboxPositionX(double)), ui->doubleSpinBox_px, SLOT(setValue(double)));
    connect(ui->openGLWidget, SIGNAL(setSpinboxPositionY(double)), ui->doubleSpinBox_py, SLOT(setValue(double)));
    connect(ui->openGLWidget, SIGNAL(setSpinboxPositionZ(double)), ui->doubleSpinBox_pz, SLOT(setValue(double)));
    connect(ui->openGLWidget, SIGNAL(setSpinboxScaleX(double)), ui->doubleSpinBox_sx, SLOT(setValue(double)));
    connect(ui->openGLWidget, SIGNAL(setSpinboxScaleY(double)), ui->doubleSpinBox_sy, SLOT(setValue(double)));
    connect(ui->openGLWidget, SIGNAL(setSpinboxScaleZ(double)), ui->doubleSpinBox_sz, SLOT(setValue(double)));
    connect(ui->openGLWidget, SIGNAL(setSpinboxRotationX(double)), ui->doubleSpinBox_rx, SLOT(setValue(double)));
    connect(ui->openGLWidget, SIGNAL(setSpinboxRotationY(double)), ui->doubleSpinBox_ry, SLOT(setValue(double)));
    connect(ui->openGLWidget, SIGNAL(setSpinboxRotationZ(double)), ui->doubleSpinBox_rz, SLOT(setValue(double)));



    connect(ui->treeView, SIGNAL(clicked(QModelIndex)), ui->openGLWidget, SLOT(selectedModel(QModelIndex)));


    //connect(ui->openGLWidget, SIGNAL(loadedMesh(std::string)), ui->treeView, SLOT(addMesh(std::string)));
    connect(ui->openGLWidget, SIGNAL(loadedModel(Model*)), ui->treeView, SLOT(addModel(Model*)));

    ui->checkBox_3->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
