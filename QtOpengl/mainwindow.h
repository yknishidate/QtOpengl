#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItem>
#include "renderwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_colorButton_clicked();

    void on_actionCube_triggered();

    void on_actionSphere_triggered();

    void on_colorButton_2_clicked();

    void on_actionRender_triggered();

    void on_actionPlane_triggered();

    void on_actionWireframe_toggled(bool arg1);

    void on_actionBackface_Culling_toggled(bool arg1);

    void on_actionDepth_Testing_toggled(bool arg1);

    void on_transColorButton_clicked();

    void on_materialTypeComboBox_currentIndexChanged(int index);

    void on_lightColorButton_clicked();

private:
    Ui::MainWindow *ui;
    RenderWindow *renderwindow;
};

#endif // MAINWINDOW_H
