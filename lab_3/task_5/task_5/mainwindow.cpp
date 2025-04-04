#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qfiledialog.h>
#include <QDesktopServices>
#include <QDir>
#include <QFileDialog>
#include <QFileInfoList>
#include <QString>

const int kDerection = 100;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      fileSystemModel(new QFileSystemModel()) {
    ui->setupUi(this);


    fileSystemModel->setRootPath(QDir::homePath());

    ui->treeView->setModel(fileSystemModel);
    ui->treeView->setRootIndex(fileSystemModel->index("/home"));
    ui->treeView->header()->resizeSections(QHeaderView::ResizeToContents);
    ui->treeView->header()->setMinimumSectionSize(kDerection);
    ui->treeView->header()->setSectionResizeMode(0, QHeaderView::Stretch);

    long long dirs_count = 0;
    long long files_count = 0;
    dirsAndFilesCount(QDir::homePath(), dirs_count, files_count);
    ui->folderEdit->setText(QString::number(dirs_count));
    ui->fileEdit->setText(QString::number(files_count));

    connect(ui->dirButton, &QPushButton::clicked, this, &MainWindow::open);
    connect(ui->treeView, &QTreeView::doubleClicked, this,
            &MainWindow::openFile);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::open() {
    QString dir_path = QFileDialog::getExistingDirectory(
        this, "Select Folder",
        fileSystemModel->filePath(ui->treeView->rootIndex()));
    if (dir_path.isEmpty()) {
        return;
    }
    ui->treeView->setRootIndex(fileSystemModel->index(dir_path));
    long long dirs_count = 0;
    long long files_count = 0;
    dirsAndFilesCount(dir_path, dirs_count, files_count);
    ui->folderEdit->setText(QString::number(dirs_count));
    ui->fileEdit->setText(QString::number(files_count));
}

void MainWindow::dirsAndFilesCount(const QString& dir_path,
                                   long long& dirs_count,
                                   long long& filesCount) {
    QDir dir(dir_path);
    for (const QFileInfo& entry :
         dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot)) {
        if (entry.isDir()) {
            dirs_count++;
            dirsAndFilesCount(
                entry.absolutePath() + "/" + entry.completeBaseName() + "/",
                dirs_count, filesCount);
        } else {
            filesCount++;
        }
    }
}

void MainWindow::openFile(QModelIndex index) {
    QFileInfo file(fileSystemModel->filePath(index));
    if (!file.isDir()) {
        QDesktopServices::openUrl(fileSystemModel->filePath(index));
    }
}
