#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "mainwidget.h"
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    /**
     * @brief Converts the int value to a double, divided by 10, and passes it to the bottleneck position spin box
     * @param value the int value to convert and pass
     */
    void bottleneckPositionConversionToSpinBox(int value);
    /**
     * @brief Converts the double value to an int, multiplied by 10, and passes it to the bottleneck position slider
     * @param value the double value to convert and pass
     */
    void bottleneckPositionConversionToSlider(double value);

private:
    Ui::MainWindow *ui;
    // Bottleneck position spin box
    QDoubleSpinBox* bottleneckPositionSpinBox;
    // Bottleneck position slider
    QSlider* bottleneckPositionSlider;
};

#endif // MAINWINDOW_H
