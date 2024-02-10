#ifndef SCREENSHOT_COMPARISON_WIDGET_H
#define SCREENSHOT_COMPARISON_WIDGET_H

#include <QWidget>
#include <QPixmap>

namespace Ui {
class ScreenshotComparisonWidget;
}

class ScreenshotComparisonWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenshotComparisonWidget(const QPixmap& image = QPixmap(), int matchPercentages = 0, QWidget *parent = nullptr);
    ~ScreenshotComparisonWidget();

private:
    Ui::ScreenshotComparisonWidget *ui;
    const QPixmap _screenshot;
    int _matchPercentages;
};

#endif // SCREENSHOT_COMPARISON_WIDGET_H
