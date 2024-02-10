#ifndef SCREENCAPTURE_H
#define SCREENCAPTURE_H

#include <QObject>
#include <QGuiApplication>
#include <QPixmap>
#include <QScreen>
class ScreenCapture : public QObject
{
    Q_OBJECT
public:
    explicit ScreenCapture(QObject *parent = nullptr);

public:
    QImage getScreenShot();
};

#endif // SCREENCAPTURE_H
