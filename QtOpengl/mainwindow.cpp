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

    // Options
    connect(ui->checkBox,   SIGNAL(toggled(bool)), ui->openGLWidget, SLOT(setDisplayMode(bool)));
    connect(ui->checkBox_2, SIGNAL(toggled(bool)), ui->openGLWidget, SLOT(setCullFace(bool)));
    connect(ui->checkBox_3, SIGNAL(toggled(bool)), ui->openGLWidget, SLOT(setDepthTest(bool)));
    ui->checkBox_3->setChecked(true);

    // Menu Bar
    connect(ui->actionOpen, SIGNAL(triggered()), ui->openGLWidget, SLOT(open()));

    // Tree View
    connect(ui->treeView, SIGNAL(clicked(QModelIndex)), ui->openGLWidget, SLOT(selectedModel(QModelIndex)));
    connect(ui->openGLWidget, SIGNAL(loadedModel(Model*)), ui->treeView, SLOT(addModel(Model*)));

    // Attibute Group
    ui->attributesGroup->setVisible(false);
    connect(ui->treeView, SIGNAL(clicked(QModelIndex)), ui->attributesGroup, SLOT(setVisibleTrue(QModelIndex)));

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

    // Texture
    connect(ui->toolButton, SIGNAL(clicked()), ui->openGLWidget, SLOT(openTexture()));
    connect(ui->openGLWidget, SIGNAL(loadedTexture(QString)), ui->lineEdit, SLOT(setText(QString)));
    ui->lineEdit->setReadOnly(true);
    connect(ui->openGLWidget, SIGNAL(setTextureName(QString)), ui->lineEdit, SLOT(setText(QString)));

    // Color
    QPalette pal = ui->colorButton->palette();
    pal.setColor(QPalette::Button, QColor(178.5f, 178.5f, 178.5f));
    ui->colorButton->setPalette(pal);
    connect(ui->openGLWidget, SIGNAL(setColorButton(QColor)), ui->colorButton, SLOT(setColor(QColor)));
    ui->colorButton_2->setPalette(pal);
    connect(ui->openGLWidget, SIGNAL(setColorButton_2(QColor)), ui->colorButton_2, SLOT(setColor(QColor)));

    // Shine Slider
    connect(ui->shineSlider, SIGNAL(valueChanged(int)), ui->openGLWidget, SLOT(setShininess(int)));
    connect(ui->openGLWidget, SIGNAL(setShininessSlider(int)), ui->shineSlider, SLOT(setValue(int)));

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

void MainWindow::on_actionCube_triggered()
{
    ui->openGLWidget->createPrimitive(1);
}
void MainWindow::on_actionSphere_triggered()
{
    ui->openGLWidget->createPrimitive(2);
}
