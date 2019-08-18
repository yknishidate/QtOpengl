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

    connect(ui->openGLWidget, SIGNAL(openedMesh(std::string)), ui->treeView, SLOT(addMesh(std::string)));
    ui->checkBox_3->setChecked(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}
