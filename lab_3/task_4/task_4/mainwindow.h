#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

   protected:
    void paintEvent(QPaintEvent* event) override;

   private slots:
    void CalculateHelper();

   private:
    bool Valid(const QString& input);
    void FillingVector(int n);
    void Hanoi(int n, int from_peg, int to_peg, QVector<int>& first,
               QVector<int>& second, QVector<int>& third);
    void Operation(int from_peg, int to_peg, QVector<int>& first,
                   QVector<int>& second, QVector<int>& third);
    void Painter(QPainter& painter, QVector<int> vector, int index, int base_x,
                 int base_y);

    Ui::MainWindow* ui;

    QVector<int> our_vector_1_;
    QVector<int> our_vector_2_;
    QVector<int> our_vector_3_;
};

#endif	// MAINWINDOW_H
