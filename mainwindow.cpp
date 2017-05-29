#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
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

void MainWindow::showFloatSummary(struct FloatSummary summary) {
    if (model != nullptr) {
        delete model;
    }

    model = new QStandardItemModel(2, 3, this);
    QStringList rows, cols;

    cols.append("x");
    cols.append("y");
    cols.append("+");

    rows.append("bisekcja");
    rows.append("regula falsi");
    rows.append("sieczne");

    model->index(1,1, model->index(0,0));
    model->setHorizontalHeaderLabels(rows);
    model->setVerticalHeaderLabels(cols);

    model->setItem(0, 0, new QStandardItem(QString::fromStdString(summary.bisection.x)));
    model->setItem(1, 0, new QStandardItem(QString::fromStdString(summary.bisection.y)));
    model->setItem(2, 0, new QStandardItem(QString::fromStdString(summary.bisection.more)));
    model->setItem(0, 1, new QStandardItem(QString::fromStdString(summary.regulafalsi.x)));
    model->setItem(1, 1, new QStandardItem(QString::fromStdString(summary.regulafalsi.y)));
    model->setItem(2, 1, new QStandardItem(QString::fromStdString(summary.regulafalsi.more)));
    model->setItem(0, 2, new QStandardItem(QString::fromStdString(summary.secant.x)));
    model->setItem(1, 2, new QStandardItem(QString::fromStdString(summary.secant.y)));
    model->setItem(2, 2, new QStandardItem(QString::fromStdString(summary.secant.more)));

    ui->result->setModel(model);
    ui->result->resizeRowsToContents();
    ui->result->resizeColumnsToContents();
}

void MainWindow::showIntervalSummary(struct IntervalSummary summary) {
    if (model != nullptr) {
        delete model;
    }

    model = new QStandardItemModel(2, 3, this);
    QStringList rows, cols;

    cols.append("x");
    cols.append("m(x)");
    cols.append("d(x)");
    cols.append("y");
    cols.append("+");

    rows.append("bisekcja");
    rows.append("regula falsi");
    rows.append("sieczne");

    model->index(1,1, model->index(0,0));
    model->setHorizontalHeaderLabels(rows);
    model->setVerticalHeaderLabels(cols);

    model->setItem(0, 0, new QStandardItem(QString::fromStdString(summary.bisection.x)));
    model->setItem(1, 0, new QStandardItem(QString::fromStdString(summary.bisection.median)));
    model->setItem(2, 0, new QStandardItem(QString::fromStdString(summary.bisection.width)));
    model->setItem(3, 0, new QStandardItem(QString::fromStdString(summary.bisection.y)));
    model->setItem(4, 0, new QStandardItem(QString::fromStdString(summary.bisection.more)));
    model->setItem(0, 1, new QStandardItem(QString::fromStdString(summary.regulafalsi.x)));
    model->setItem(1, 1, new QStandardItem(QString::fromStdString(summary.regulafalsi.median)));
    model->setItem(2, 1, new QStandardItem(QString::fromStdString(summary.regulafalsi.width)));
    model->setItem(3, 1, new QStandardItem(QString::fromStdString(summary.regulafalsi.y)));
    model->setItem(4, 1, new QStandardItem(QString::fromStdString(summary.regulafalsi.more)));
    model->setItem(0, 2, new QStandardItem(QString::fromStdString(summary.secant.x)));
    model->setItem(1, 2, new QStandardItem(QString::fromStdString(summary.secant.median)));
    model->setItem(2, 2, new QStandardItem(QString::fromStdString(summary.secant.width)));
    model->setItem(3, 2, new QStandardItem(QString::fromStdString(summary.secant.y)));
    model->setItem(4, 2, new QStandardItem(QString::fromStdString(summary.secant.more)));

    ui->result->setModel(model);
    ui->result->resizeRowsToContents();
    ui->result->resizeColumnsToContents();
}

void MainWindow::on_loadFunction_clicked()
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

    ui->solve->setEnabled(true);
}

void MainWindow::on_solve_clicked()
{
    std::string a_str, b_str;
    int mode;
    a_str = ui->aInput->text().toStdString();
    b_str = ui->bInput->text().toStdString();
    mode = ui->intervalArithmetic->isChecked();
    backend.decimals = ui->decimals->value();
    backend.bisectionTolerance = pow(10.0l, ui->bisectionTolerance->value());
    backend.bisectionIterations = ui->bisectionIterations->value();

    try {
        if (mode == 1) {
            struct IntervalSummary output = backend.solveInterval(a_str, b_str);
            showIntervalSummary(output);
        } else {
            struct FloatSummary output = backend.solveFloatingPoint(a_str, b_str);
            showFloatSummary(output);
        }
    } catch (const char *error) {
        QMessageBox::warning(this, "Błąd", error);
        return;
    }
}
