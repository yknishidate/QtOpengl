#include "renderwindow.h"
#include "ui_renderwindow.h"

RenderWindow::RenderWindow(QWidget *parent, float x, float y, float l, std::vector<Model *> m) :
    QMainWindow(parent),
    ui(new Ui::RenderWindow)
{
    ui->setupUi(this);

    connect(ui->stopRenderingButton, SIGNAL(clicked()), ui->renderWidget, SLOT(stopRendering()) );
    connect(ui->startRenderingButton, SIGNAL(clicked()), ui->renderWidget, SLOT(startRendering()) );
    ui->renderWidget->setXRot(x);
    ui->renderWidget->setYRot(y);
    ui->renderWidget->setCameraDistance(l);
    ui->renderWidget->setModels(m);
}

RenderWindow::~RenderWindow()
{
    delete ui;
}

void RenderWindow::on_renderPassBox_currentIndexChanged(int index)
{
    ui->renderWidget->changeRenderMode(index);
    qDebug() << "Render Mode Changed:" << index;
}

void RenderWindow::on_saveButton_clicked()
{
    qDebug() << "Clicked Save Button";
    ui->renderWidget->saveImage();
}
