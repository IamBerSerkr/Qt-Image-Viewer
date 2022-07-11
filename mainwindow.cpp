#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      fileMenu(nullptr),
      openAction(nullptr)
{
    initUI();
    return;
}

MainWindow::~MainWindow()
{
}

void MainWindow::initUI()
{
    this->resize(800, 600);

    fileMenu = menuBar()->addMenu(tr("&File"));
    createAction();

    return;
}

void MainWindow::createAction()
{
    openAction = new QAction(tr("&Open"), this);
    openAction->setShortcut(QKeySequence::Open);

    fileMenu->addAction(openAction);

    connect(openAction, SIGNAL(triggered(bool)), this, SLOT(openImage()));
    return;
}


void MainWindow::initImageFileDialog(QFileDialog& dialog)
{
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter("Images (*.png *.bmp *.jpg)");

    return;
}

QString MainWindow::getImageNameFromPath(const QString& path)
{
    QStringList list = path.split("/");
    return list.back();
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

void MainWindow::openImage()
{
    QString path;
    readImagePath(path);

    QString imageName = getImageNameFromPath(path);

    qDebug() << path;
    QDockWidget *newDockWidget = new QDockWidget(this);
    newDockWidget->setWidget(new QImageViewer(path, this));
    newDockWidget->setWindowTitle(imageName);


    addDockWidget(Qt::LeftDockWidgetArea,
                  static_cast<QDockWidget*>(newDockWidget));

    if (1 <= imageViewers.size())
    {
        tabifyDockWidget(newDockWidget,
                         static_cast<QDockWidget*>(imageViewers.back()));
        newDockWidget->setVisible(true);
        newDockWidget->raise();
    }

    imageViewers.push_back(newDockWidget);
    return;
}


