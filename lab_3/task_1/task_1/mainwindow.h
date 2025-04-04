#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "manager.h"

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

   private:
    Ui::MainWindow* ui;

    Manager manager_;

   private slots:
    void AddNumber();
};
#endif	// MAINWINDOW_H
