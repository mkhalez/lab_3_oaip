#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QFileDialog>
#include <QFileInfoList>
#include <QString>

const int kScreenWidth = 200;
const int kScreenLength = 400;


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setFixedSize(kScreenLength, kScreenWidth);

    connect(ui->dirButton, &QPushButton::clicked, this, &MainWindow::OpenDir);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::OpenDir() {
    ui->fileEdit->clear();
    ui->folderEdit->clear();
    dir_ = QFileDialog::getExistingDirectory(this, "Выберите директорию");


    if (dir_ != "") {
        int files = 0, folders = 0;
        CountFilesAndFolders(dir_, folders, files);

        ui->fileEdit->setText(QString::number(files));
        ui->folderEdit->setText(QString::number(folders));
    }
}


void MainWindow::CountFilesAndFolders(const QString& dir_path,
                                      int& folder_count, int& file_count) {
    QDir dir(dir_path);

    if (!dir.exists()) {
        return;
    }

    //список файлов и папок
    QFileInfoList list =
        dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);


    for (const QFileInfo& info : list) {
        if (info.isDir()) {
            folder_count++;
            CountFilesAndFolders(info.absoluteFilePath(), folder_count,
                                 file_count);

        } else if (info.isFile()) {
            file_count++;
        }
    }
}
