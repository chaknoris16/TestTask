#include "../include/screen_capture.h"

ScreenCapture::ScreenCapture(QObject *parent)
    : QObject{parent}
{}

QImage ScreenCapture::getScreenShot()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    QPixmap screenshot = screen->grabWindow(0, screenGeometry.x(), screenGeometry.y(), screenGeometry.width(), screenGeometry.height());

    return screenshot.toImage();
}
