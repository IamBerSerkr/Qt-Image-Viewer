#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->setMaximumHeight(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initImageFileDialog(QFileDialog& dialog)
{
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter("Images (*.png *.bmp *.jpg)");

    return;
}

QString MainWindow::getImageNameFromPath(const QString& path)
{
    QStringList list = path.split("/"); // check later
    return list.back();
}

void MainWindow::tabifyImageViewers(QWidget* newImageViewer)
{
    for (const auto& viewer : imageViewers)
    {
        tabifyDockWidget(static_cast<QDockWidget*>(newImageViewer),
                         static_cast<QDockWidget*>(viewer));
    }

    return;
}

void MainWindow::readImagePath(QString& path)
{
    QFileDialog dialog(this, tr("Open File"));
    initImageFileDialog(dialog);

    QStringList filePaths;
    if (dialog.exec())
    {
        filePaths = dialog.selectedFiles();
        path = filePaths.at(0);
    }
    return;
}

void MainWindow::on_actionOpen_triggered()
{
    QString path;
    readImagePath(path);

    QString imageName = getImageNameFromPath(path);

    qDebug() << path;

    // refactor error handling
    if (path.isEmpty())
    {
        qDebug() << "failed to open the image";
        return;
    }
    QDockWidget *newDockWidget = new QDockWidget(this);
    newDockWidget->setWidget(new ImageViewer(path, this));
    newDockWidget->setWindowTitle(imageName);

    //  fix later
    //    newDockWidget->setAttribute(Qt::WA_DeleteOnClose);

    addDockWidget(Qt::TopDockWidgetArea,
                  static_cast<QDockWidget*>(newDockWidget));

    tabifyImageViewers(newDockWidget);

    newDockWidget->setVisible(true);
    newDockWidget->raise();
    imageViewers.push_back(newDockWidget);

    return;
}

