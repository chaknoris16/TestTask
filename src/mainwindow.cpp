#include "../include/mainwindow.h"
#include "ui/ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->gridLayout->setColumnStretch(1, 1);
    this->db_manager->createTable("database.db");


    connect( ui->pushButton, &QPushButton::clicked, this, &MainWindow::toggleProcessing );
    connect(this->timer, &QTimer::timeout, this, [this](){
        if(this->currentImage.isNull()) {
            this->currentImage = screenCapture->getScreenShot();
            ui->gridLayout->addWidget(new ScreenshotComparisonWidget(QPixmap::fromImage(this->currentImage), 0, ui->scrollAreaWidgetContents));
            qDebug()<< "it is first work";
        }else {
            this->newImge = screenCapture->getScreenShot();
            startImageProcessing();
        }
    });
    connect(imageComparator, &ImageComparator::resultReady, this, &MainWindow::handleResult);

    fillGridAndSetCurrentImage(this->db_manager->loadImageDataFromDatabase(), this->currentImage);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete imageComparator;
}

void MainWindow::startImageProcessing()
{
    QThread* thread = new QThread;

    QImage image1 = this->currentImage;
    QImage image2 = this->newImge;

    auto processImagesLambda = [this, image1, image2]() {
        imageComparator->calculateImageSimilarityPercentage(image1, image2);

        QThread::currentThread()->quit();
        QThread::currentThread()->deleteLater();
    };

    connect(thread, &QThread::started, processImagesLambda);

    thread->start();
}

void MainWindow::fillGridAndSetCurrentImage(const QVector<QPair<QImage, int> > &dbData, QImage &currentImage)
{
    if(!dbData.isEmpty()) {
        for (auto& block : dbData) {
            ui->gridLayout->addWidget(new ScreenshotComparisonWidget(QPixmap::fromImage(block.first), block.second, ui->scrollAreaWidgetContents));
        }

        currentImage = dbData.front().first;
    }
}

void MainWindow::toggleProcessing()
{
    if (this->timer->isActive()) {
        this->timer->stop();
        ui->pushButton->setText("Start");
    } else {
        this->timer->start(TIMER_INTERVAL_MS);
        ui->pushButton->setText("Stop");
    }
}

void MainWindow::handleResult(double percentageMatch)
{
    db_manager->saveData(this->newImge, percentageMatch);
    ui->gridLayout->addWidget(new ScreenshotComparisonWidget(QPixmap::fromImage(newImge), percentageMatch, ui->scrollAreaWidgetContents));
    this->currentImage = this->newImge;
}
