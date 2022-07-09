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
    // set up check box
    fitToScreenCheckBox = new QCheckBox(this),
    fitToScreenCheckBox->setText(tr("Fit to Screen"));
    fitToScreenCheckBox->setCheckable(true);
    fitToScreenCheckBox->setChecked(false);
    connect(fitToScreenCheckBox, SIGNAL(stateChanged(int)),
                                 this, SLOT(checkFittingOption(int)));

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

    if (!fitToScreenCheckBox->isChecked())
    {
        imageLabel->adjustSize();
    }

    return;
}

void QImageViewer::checkFittingOption(int state)
{
    if (Qt::Checked == state)
    {
        qDebug() << "checked!";
        scrollArea->setWidgetResizable(true);
    }
    else if (Qt::Unchecked == state)
    {
        qDebug() << "unchecked!";
        scrollArea->setWidgetResizable(false);
        imageLabel->adjustSize();
    }
    else
    {
        qDebug() << ")-: Something went wrong! :-(";
    }

    return;
}


