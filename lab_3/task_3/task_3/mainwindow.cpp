#include "mainwindow.h"
#include <QMessageBox>
#include "manager.h"
#include "ui_mainwindow.h"


const int kLengthScreen = 350;
const int kWeigthScreen = 200;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->inputEdit->setFocus();
    this->setFixedSize(kLengthScreen, kWeigthScreen);

    connect(ui->calculateButton, &QPushButton::clicked, this,
            &MainWindow::Calculate);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::Calculate() {
    QString input = ui->inputEdit->text();
    Manager manager;
    if (manager.Check(input)) {
        long number = input.toLong();


        long result = manager.Reverse(number);

        ui->resultEdit->setText(QString::number(result));
    } else {
        QMessageBox::warning(this, "Ошибка ввода",
                             "Введите целое число, не начинающаяся с нулей и "
                             "не заканчивающаяся нулями и число максимум может "
                             "стоять из 19 цифр");
        ui->inputEdit->clear();
        ui->resultEdit->clear();
        ui->inputEdit->setFocus();
    }
}
