#include "mainwindow.h"
#include <QMessageBox>
#include "ui_mainwindow.h"
#include "valid.h"

const int kMaxNumberAfterPoint = 12;
const int kAverageValue = 6;
const int kLengthScreen = 532;
const int kWidthScreen = 215;
const int kAfterMax = 9;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);


    ui->accuracySpinBox->setRange(1, kMaxNumberAfterPoint);
    ui->accuracySpinBox->setValue(kAverageValue);
    ui->accuracySpinBox->setSingleStep(1);

    ui->inputEdit->setFocus();
    ui->resultEdit->setReadOnly(true);
    this->setFixedSize(kLengthScreen, kWidthScreen);


    connect(ui->calculateButton, &QPushButton::clicked, this,
            &MainWindow::AddNumber);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::AddNumber() {

    QString input = ui->inputEdit->text();

    Valid valid;
    if (input.indexOf(".") > kAverageValue ||
        (input.indexOf(".") == -1 && input.length() > kAfterMax)) {
        QMessageBox::warning(this, "Ошибка ввода",
                             "Введите меньше знаков перед запятой и целая "
                             "часть может состоять максимум из 6 цифр");

        ui->inputEdit->clear();
        ui->resultEdit->clear();
        ui->inputEdit->setFocus();
    } else if (valid.CheckInput(input)) {
        manager_.SetAccuracy(ui->accuracySpinBox->value());
        double number = input.toDouble();
        double number_abs = qAbs(number);
        int int_part = (int)number_abs;
        double fract_part = (number_abs - int_part);
        QString result = manager_.TransformationToBin(int_part, fract_part,
                                                      false, false, ".");


        result = (number < 0) ? "1" + result : "0" + result;

        ui->resultEdit->setText(result);
    } else {

        QMessageBox::warning(
            this, "Ошибка ввода",
            "Введено некорректное значение. Пожалуйста, введите число.");

        ui->inputEdit->clear();
        ui->resultEdit->clear();
        ui->inputEdit->setFocus();
    }
}
