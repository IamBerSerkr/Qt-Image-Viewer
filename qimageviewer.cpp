#include "qimageviewer.h"

QImageViewer::QImageViewer(const QString& path, QWidget *parent)
    : QWidget{parent},
      verticalLayout(nullptr),
      imageLabel(nullptr),
      scrollArea(nullptr)
{
    loadImage(path);
    initUI();
}

QImageViewer::~QImageViewer()
{

}

void QImageViewer::initUI()
{
    fitToScreenCheckBox = new QCheckBox(this),
    fitToScreenCheckBox->setText(tr("Fit to Screen"));
    fitToScreenCheckBox->setCheckable(true);
    fitToScreenCheckBox->setChecked(false);

    imageLabel = new QLabel(this);
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored,
                              QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea = new QScrollArea(this);
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    scrollArea->setVisible(false);

    verticalLayout = new QVBoxLayout(this);
    verticalLayout->addWidget(fitToScreenCheckBox);
    verticalLayout->addWidget(scrollArea);

    showImage();

    return;
}

void QImageViewer::loadImage(const QString &path)
{
    QImageReader reader(path);
    reader.setAutoTransform(true);

    image = reader.read();

    // TODO: check the success of image reading
    return;
}

void QImageViewer::showImage()
{
    imageLabel->setPixmap(QPixmap::fromImage(image));
    scrollArea->setVisible(true);
    imageLabel->adjustSize();

    return;
}


