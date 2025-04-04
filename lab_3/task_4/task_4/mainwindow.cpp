#include "mainwindow.h"
#include <QMessageBox>
#include <QPainter>
#include <QThread>
#include "ui_mainwindow.h"

const int kLengthScreen = 700;
const int kWeigthScreen = 700;

const int kTowerX1 = 100;
const int kTowerX2 = 250;
const int kTowerX3 = 500;
const int kTowerY = 400;
const int kMaxNumber = 8;
const int kSumTower = 6;
const int kSleep = 500;
const int kPixel20 = 20;


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    our_vector_1_ = {};
    our_vector_2_ = {};
    our_vector_3_ = {};
    this->setFixedSize(kLengthScreen, kWeigthScreen);

    connect(ui->calculateButton, &QPushButton::clicked, this,
            &MainWindow::CalculateHelper);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::CalculateHelper() {

    our_vector_1_.clear();
    our_vector_2_.clear();
    our_vector_3_.clear();

    update();
    QCoreApplication::processEvents();

    QString input = ui->inputEdit->text();

    if (!Valid(input)) {
        QMessageBox::warning(this, "Ошибка ввода",
                             "Введите натуральное число в пределах от 1 до 8");
        ui->inputEdit->clear();
        ui->inputEdit->setFocus();
        return;
    }

    int number_of_item = input.toInt();
    FillingVector(number_of_item);
    Hanoi(number_of_item, 1, 3, our_vector_1_, our_vector_2_, our_vector_3_);
}

void MainWindow::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    Painter(painter, our_vector_1_, 0, kTowerX1, kTowerY);
    Painter(painter, our_vector_2_, 0, kTowerX2, kTowerY);
    Painter(painter, our_vector_3_, 0, kTowerX3, kTowerY);
}


void MainWindow::FillingVector(int n) {


    for (int i = 1; i <= n; i++) {
        our_vector_1_.push_front(i);
    }
}
bool MainWindow::Valid(const QString& input) {
    bool ok;
    int number = input.toInt(&ok);


    if (!ok) {
        return false;
    }


    if (number < 0 || number > kMaxNumber) {
        return false;
    }

    return true;
}

void MainWindow::Hanoi(int n, int from_peg, int to_peg, QVector<int>& first,
                       QVector<int>& second, QVector<int>& third) {


    if (n == 1) {
        Operation(from_peg, to_peg, first, second, third);
        return;
    }

    int unused_peg = kSumTower - from_peg - to_peg;
    Hanoi(n - 1, from_peg, unused_peg, first, second, third);
    Operation(from_peg, to_peg, first, second, third);
    Hanoi(n - 1, unused_peg, to_peg, first, second, third);
}


void MainWindow::Operation(int from_peg, int to_peg, QVector<int>& first,
                           QVector<int>& second, QVector<int>& third) {
    int num;


    switch (from_peg) {
        case 1: {
            if (first.size() == 0) {
                return;
            }
            num = first[first.size() - 1];
            to_peg == 2 ? second.push_back(num) : third.push_back(num);
            first.pop_back();
            break;
        }
        case 2: {
            if (second.size() == 0) {
                return;
            }
            num = second[second.size() - 1];
            to_peg == 1 ? first.push_back(num) : third.push_back(num);
            second.pop_back();
            break;
        }
        case 3: {
            if (third.size() == 0) {
                return;
            }
            num = third[third.size() - 1];
            to_peg == 1 ? first.push_back(num) : second.push_back(num);
            third.pop_back();
            break;
        }
    }
    update();
    QCoreApplication::processEvents();
    QThread::msleep(kSleep);
}

void MainWindow::Painter(QPainter& painter, QVector<int> vector, int index,
                         int base_x, int base_y) {
    if (index >= vector.size()) {
        return;
    }

    int length = vector[index] * kPixel20;
    int width = kPixel20;
    int x = base_x - length / 2;
    int y = base_y - (index)*kPixel20;

    painter.setPen(QPen(Qt::black, 2));
    painter.drawRect(x, y, length, width);

    Painter(painter, vector, index + 1, base_x, base_y);
}
