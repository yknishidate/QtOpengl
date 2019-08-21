#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItem>

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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
