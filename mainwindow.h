#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QVector>
#include <QMenuBar>
#include <QString>
#include <QFileDialog>
#include <QDockWidget>
#include <imageviewer.h>

#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void readImagePath(QString&);
    void initImageFileDialog(QFileDialog&);
    QString getImageNameFromPath(const QString&);
    void tabifyImageViewers(QWidget*);

private slots:
    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;

    QVector<QWidget*> imageViewers;
};
#endif // MAINWINDOW_H
