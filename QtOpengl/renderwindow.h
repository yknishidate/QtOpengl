#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <QMainWindow>
#include <QMatrix4x4>
#include "camera.h"

namespace Ui {
class RenderWindow;
}

class RenderWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RenderWindow(QWidget *parent = nullptr, float t = 0.0f, float p = 0.0f);
    ~RenderWindow();

private:
    Ui::RenderWindow *ui;
};

#endif // RENDERWINDOW_H
