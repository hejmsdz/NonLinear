#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "backend.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Backend backend;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionLoadFunction_triggered();

    void on_actionSolve_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
