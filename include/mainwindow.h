#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "screenshot_comparison_widget.h"
#include "screen_capture.h"
#include "imagecomparator.h"
#include "db_manager.h"
#include <QImage>
#include <QTimer>
#include <QThread>

constexpr int TIMER_INTERVAL_MS = 60'000;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QTimer* timer = new QTimer(this);
    ScreenCapture* screenCapture = new ScreenCapture(this);
    ImageComparator* imageComparator = new ImageComparator();
    DBManager* db_manager = new DBManager(this);
    QImage currentImage{};
    QImage newImge{};
    void startImageProcessing();
    void fillGridAndSetCurrentImage(const QVector<QPair<QImage, int> > &dbData, QImage& currentImage);

private slots:
    void toggleProcessing();
    void handleResult(double percentageMatch);

};
#endif // MAINWINDOW_H
