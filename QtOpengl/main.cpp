#include "mainwindow.h"
#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setSamples(16);
    format.setVersion(2, 0);
    QSurfaceFormat::setDefaultFormat(format);

    MainWindow w;
    w.show();


    return a.exec();
}
