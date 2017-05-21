#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "backend.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Backend backend;
    QStandardItemModel *model = nullptr;

    void showFloatSummary(struct FloatSummary summary);
    void showIntervalSummary(struct IntervalSummary summary);

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
