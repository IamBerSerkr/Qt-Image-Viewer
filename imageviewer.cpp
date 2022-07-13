#include "imageviewer.h"
#include "ui_imageviewer.h"

ImageViewer::ImageViewer(const QString& path, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageViewer),
    graphicsScene(nullptr)
{
    ui->setupUi(this);
    graphicsScene = new QGraphicsScene();
    ui->graphicsView->setScene(graphicsScene);

    readImage(path);
    showImage();
}

ImageViewer::~ImageViewer()
{
    delete ui;
}

void ImageViewer::readImage(const QString& path)
{
    imageMat = cv::imread(path.toStdString(), cv::IMREAD_UNCHANGED);
    imagePixmap = CvMatToQPixmap(imageMat);

    return;
}

void ImageViewer::showImage()
{
    ui->graphicsView->resetTransform();
    graphicsScene->addPixmap(imagePixmap);
    graphicsScene->update();
    ui->graphicsView->setSceneRect(imagePixmap.rect());
    graphicsScene->setSceneRect(imagePixmap.rect());
    return;
}

QPixmap ImageViewer::CvMatToQPixmap(const cv::Mat& inputMat)
{
    switch ( inputMat.type() )
          {
             // 8-bit, 4 channel
             case CV_8UC4:
             {
                QImage qimage(inputMat.data,
                              inputMat.cols, inputMat.rows,
                              static_cast<int>(inputMat.step),
                              QImage::Format_ARGB32);

                return QPixmap::fromImage(qimage);
             }

             // 8-bit, 3 channel
             case CV_8UC3:
             {
                QImage qimage(inputMat.data,
                              inputMat.cols, inputMat.rows,
                              static_cast<int>(inputMat.step),
                              QImage::Format_RGB888);

                return QPixmap::fromImage(qimage.rgbSwapped());
             }

             // 8-bit, 1 channel
             case CV_8UC1:
             {
                QImage qimage(inputMat.data,
                              inputMat.cols, inputMat.rows,
                              static_cast<int>(inputMat.step),
                              QImage::Format_Grayscale8);

                return QPixmap::fromImage(qimage);
             }

             default:
                qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inputMat.type();
                break;
          }

          return QPixmap();
}
