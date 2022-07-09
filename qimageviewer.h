#ifndef QIMAGEVIEWER_H
#define QIMAGEVIEWER_H

#include <QWidget>
#include <QString>
#include <QLabel>
#include <QScrollArea>
#include <QImageReader>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QCheckBox>

class QImageViewer : public QWidget
{
    Q_OBJECT
public:
    QImageViewer(const QString& path, QWidget *parent = nullptr);
    ~QImageViewer();
private:
    void initUI();
    void loadImage(const QString& path);
    void showImage();

private slots:
    void checkFittingOption(int);

private:
    QVBoxLayout *verticalLayout;

    QCheckBox *fitToScreenCheckBox;

    QImage image;
    QLabel *imageLabel;
    QScrollArea *scrollArea;
};

#endif // QIMAGEVIEWER_H
