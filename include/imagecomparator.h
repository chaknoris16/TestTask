#ifndef IMAGECOMPARATOR_H
#define IMAGECOMPARATOR_H

#include <QObject>
#include <QImage>
#include <QDebug>
#include <opencv2/opencv.hpp>

class ImageComparator : public QObject
{
    Q_OBJECT
public:
    explicit ImageComparator(QObject *parent = nullptr);
    void calculateImageSimilarityPercentage(const QImage& image1, const QImage& image2);
signals:
    void resultReady(double percentageMatch);
private:
    cv::Mat QImageToMat(const QImage &image);
};

#endif // IMAGECOMPARATOR_H
