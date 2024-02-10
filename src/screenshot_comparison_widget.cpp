#include "../include/screenshot_comparison_widget.h"
#include "ui/ui_screenshot_comparison_widget.h"

ScreenshotComparisonWidget::ScreenshotComparisonWidget(const QPixmap &image, int matchPercentages, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ScreenshotComparisonWidget),
    _screenshot{image},
    _matchPercentages{matchPercentages}
{
    ui->setupUi(this);
    ui->ImageLabel->setPixmap(_screenshot);
    ui->percentLable->setText(QString::number(_matchPercentages) + '%');
}

ScreenshotComparisonWidget::~ScreenshotComparisonWidget()
{
    delete ui;
}
