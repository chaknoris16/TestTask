#include "../include/imagecomparator.h"

ImageComparator::ImageComparator(QObject *parent)
    : QObject{parent}
{}

void ImageComparator::calculateImageSimilarityPercentage(const QImage& image1, const QImage& image2)
{
    qDebug() << "calculateImageSimilarityPercentage";
    cv::Mat gray1, gray2;
    cv::cvtColor(QImageToMat(image1), gray1, cv::COLOR_BGR2GRAY);
    cv::cvtColor(QImageToMat(image2), gray2, cv::COLOR_BGR2GRAY);

    cv::Mat diff;
    cv::absdiff(gray1, gray2, diff);

    int nonZeroPixels = cv::countNonZero(diff);
    int totalPixels = gray1.rows * gray1.cols;

    double percentageMatch = (1.0 - static_cast<double>(nonZeroPixels) / totalPixels) * 100.0;

    emit resultReady(percentageMatch);
}

cv::Mat ImageComparator::QImageToMat(const QImage &image)
{
    qDebug() << "QImageToMat";
    cv::Mat mat = cv::Mat(image.height(), image.width(), CV_8UC4, const_cast<uchar*>(image.bits()), static_cast<int>(image.bytesPerLine())).clone();
    cv::cvtColor(mat, mat, cv::COLOR_RGBA2BGR);
    return mat;
}
