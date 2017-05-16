#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include "sofunction.h"
#include "solvers/regulafalsi.h"
#include <string>
#include <iostream>
#include <iomanip>

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

void MainWindow::on_actionSolve_triggered()
{
    if (function == nullptr) {
        QMessageBox::warning(this, "Błąd", "Najpierw wczytaj funkcję!");
        return;
    }

    std::string a_str = ui->aInput->text().toStdString();
    std::string b_str = ui->bInput->text().toStdString();

    if ((a_str+b_str).find("bla") != std::string::npos) {
        QMessageBox::warning(this, "Błąd", "Nie tym razem, panie profesorze ;)");
        return;
    }

    long double a, b;
    try {
        a = std::stold(a_str);
        b = std::stold(b_str);
    } catch (std::invalid_argument &error) {
        QMessageBox::warning(this, "Błąd", "Nie udało się zinterpretować wpisanych danych jako liczbę!");
        return;
    }

    std::cout << a << ":" << b << std::endl;


    long double x;
    std::stringstream x_str;

    try {
        x = FloatingPoint::RegulaFalsi(a, b, function);
        x_str << std::scientific;
        x_str << std::setprecision(16) << x;
    } catch(int err) {
        QMessageBox::warning(this, "Błąd", "Coś się popsuło!");
        return;
    }

    std::cout << x_str.str() << std::endl;
}
