#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include "sofunction.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete function;
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

    Function *new_function;
    try {
        new_function = new SOFunction(library_path.toLatin1().data());
    } catch (const char *error) {
        QMessageBox::warning(this, "Błąd", error);
        return;
    }

    if (function != nullptr) {
        delete function;
    }

    function = new_function;
    ui->actionSolve->setEnabled(true);
}
