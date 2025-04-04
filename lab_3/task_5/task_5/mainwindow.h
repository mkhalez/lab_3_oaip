#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void CountFilesAndFolders(const QString& dir_path, int& folder_count,
                              int& file_count);
    QString dir_;

   private slots:
    void OpenDir();
};
#endif	// MAINWINDOW_H
