#include "renderwindow.h"
#include "ui_renderwindow.h"

RenderWindow::RenderWindow(QWidget *parent, float x, float y) :
    QMainWindow(parent),
    ui(new Ui::RenderWindow)
{
    ui->setupUi(this);

    connect(ui->stopRenderingButton, SIGNAL(clicked()), ui->renderWidget, SLOT(stopRendering()) );
    qDebug()  << "---Render Window Contractor---";
    qDebug() << "View Rotation: (" << x << "," << y << ")";
    ui->renderWidget->setXRot(x);
    ui->renderWidget->setYRot(y);
}

RenderWindow::~RenderWindow()
{
    delete ui;
}
