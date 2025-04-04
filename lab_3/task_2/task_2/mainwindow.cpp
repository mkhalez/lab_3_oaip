#include "mainwindow.h"
#include <QMessageBox>
#include "manager.h"
#include "ui_mainwindow.h"

const int kLengthScreen = 532;
const int kWeigthScreen = 190;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->firstEdit->setFocus();
    this->setFixedSize(kLengthScreen, kWeigthScreen);

    connect(ui->calculateButton, &QPushButton::clicked, this,
            &MainWindow::Calculate);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::Calculate() {
    QString input_first_number = ui->firstEdit->text();
    QString input_second_number = ui->secondEdit->text();
    Manager manager;

    if (!manager.CheckInput(input_first_number) ||
        !manager.CheckInput((input_second_number))) {
        QMessageBox::warning(this, "Ошибка ввода",
                             "Введите целые неотрицательные числа");
        ui->firstEdit->clear();
        ui->secondEdit->clear();
        ui->resultEdit->clear();
        ui->firstEdit->setFocus();
        return;
    }


    long number_1 = input_first_number.toLong();
    long number_2 = input_second_number.toLong();

    int result = manager.FunctionAckerman(number_1, number_2);


    if (result == -1) {
        QMessageBox::warning(this, "Ошибка ввода", "Превышенно число итераций");
        ui->firstEdit->clear();
        ui->secondEdit->clear();
        ui->resultEdit->clear();
        ui->firstEdit->setFocus();
    } else {
        ui->resultEdit->setText(QString::number(result));
    }
}
