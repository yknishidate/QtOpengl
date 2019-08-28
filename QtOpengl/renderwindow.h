#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <QMainWindow>
#include <QMatrix4x4>
#include "camera.h"
#include "model.h"
#include <vector>

namespace Ui {
class RenderWindow;
}

class RenderWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RenderWindow(QWidget *parent = nullptr, float t = 0.0f, float p = 0.0f, float l = 10.0f, std::vector<Model *> m = {} );
    ~RenderWindow();

private slots:

    void on_renderPassBox_currentIndexChanged(int index);

    void on_saveButton_clicked();

private:
    Ui::RenderWindow *ui;
};

#endif // RENDERWINDOW_H
