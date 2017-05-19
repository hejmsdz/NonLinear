#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <string>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLoadFunction_triggered()
{
    QString library_path = QFileDialog::getOpenFileName(this, "Wczytaj funkcję",
                                                        QDir::currentPath(),
                                                        "Biblioteka dynamiczna (*.so)");

    if (library_path.isNull()) {
        return;
    }

    try {
        backend.loadFunction(library_path.toLatin1().data());
    } catch (const char *error) {
        QMessageBox::warning(this, "Błąd", error);
        return;
    }

    ui->actionSolve->setEnabled(true);
}

void MainWindow::on_actionSolve_triggered()
{
    std::string output, a_str, b_str;
    a_str = ui->aInput->text().toStdString();
    b_str = ui->bInput->text().toStdString();
    try {
        output = backend.solveFloatingPoint(a_str, b_str);
    } catch (const char *error) {
        QMessageBox::warning(this, "Błąd", error);
        return;
    }

    std::cout << output << std::endl;
}
