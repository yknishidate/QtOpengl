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

    connect(ui->doubleSpinBox_px, SIGNAL(valueChanged(double)), ui->openGLWidget, SLOT(changeModelPositionX(double)));
    connect(ui->doubleSpinBox_py, SIGNAL(valueChanged(double)), ui->openGLWidget, SLOT(changeModelPositionY(double)));
    connect(ui->doubleSpinBox_pz, SIGNAL(valueChanged(double)), ui->openGLWidget, SLOT(changeModelPositionZ(double)));

    connect(ui->doubleSpinBox_sx, SIGNAL(valueChanged(double)), ui->openGLWidget, SLOT(changeModelScaleX(double)));
    connect(ui->doubleSpinBox_sy, SIGNAL(valueChanged(double)), ui->openGLWidget, SLOT(changeModelScaleY(double)));
    connect(ui->doubleSpinBox_sz, SIGNAL(valueChanged(double)), ui->openGLWidget, SLOT(changeModelScaleZ(double)));

    connect(ui->doubleSpinBox_rx, SIGNAL(valueChanged(double)), ui->openGLWidget, SLOT(changeModelRotationX(double)));
    connect(ui->doubleSpinBox_ry, SIGNAL(valueChanged(double)), ui->openGLWidget, SLOT(changeModelRotationY(double)));
    connect(ui->doubleSpinBox_rz, SIGNAL(valueChanged(double)), ui->openGLWidget, SLOT(changeModelRotationZ(double)));


    connect(ui->openGLWidget, SIGNAL(loadedMesh(std::string)), ui->treeView, SLOT(addMesh(std::string)));
    ui->checkBox_3->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
