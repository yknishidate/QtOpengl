#include "renderwindow.h"
#include "ui_renderwindow.h"

RenderWindow::RenderWindow(QWidget *parent, float x, float y, float l, std::vector<Model *> m) :
    QMainWindow(parent),
    ui(new Ui::RenderWindow)
{
    ui->setupUi(this);

    connect(ui->stopRenderingButton, SIGNAL(clicked()), ui->renderWidget, SLOT(stopRendering()) );
    qDebug()  << "---Render Window Contractor---";
    qDebug() << "View Rotation: (" << x << "," << y << ")";
    ui->renderWidget->setXRot(x);
    ui->renderWidget->setYRot(y);
    ui->renderWidget->setCameraDistance(l);
//    ui->renderWidget->setModelsPtr(m);
    ui->renderWidget->setModels(m);
}

RenderWindow::~RenderWindow()
{
    delete ui;
}
