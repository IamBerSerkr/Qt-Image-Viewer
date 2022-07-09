#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QVector>
#include <QDockWidget>
#include <QFileDialog>
#include <qimageviewer.h>

#include <QDebug>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initUI();
    void createAction();
    void readImagePath(QString&);
    void initImageFileDialog(QFileDialog&);

private slots:
    void openImage();

private:
    QMenu *fileMenu;

    QAction *openAction;

    QVector<QWidget*> imageViewers;
};
#endif // MAINWINDOW_H
