#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPixmap>
#include <opencv2/opencv.hpp>

#include <QDebug>

namespace Ui {
class ImageViewer;
}

class ImageViewer : public QMainWindow
{
    Q_OBJECT

public:
    ImageViewer(const QString&, QWidget *parent = nullptr);
    ~ImageViewer();

private:
    void readImage(const QString&);
    void showImage();
    QPixmap CvMatToQPixmap(const cv::Mat&);


private:
    Ui::ImageViewer *ui;
    QGraphicsScene *graphicsScene;

    cv::Mat imageMat;
    QPixmap imagePixmap;
};

#endif // IMAGEVIEWER_H
