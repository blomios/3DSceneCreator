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
    /**
     * @brief Converts the int value to a double, divided by 10, and passes it to the bottleneck x size spin box
     * @param value the int value to convert and pass
     */
    void bottleneckXSizeConversionToSpinBox(int value);
    /**
     * @brief Converts the double value to an int, multiplied by 10, and passes it to the bottleneck x size slider
     * @param value the double value to convert and pass
     */
    void bottleneckXSizeConversionToSlider(double value);
    /**
     * @brief Converts the int value to a double, divided by 10, and passes it to the bottleneck y size spin box
     * @param value the int value to convert and pass
     */
    void bottleneckYSizeConversionToSpinBox(int value);
    /**
     * @brief Converts the double value to an int, multiplied by 10, and passes it to the bottleneck y size slider
     * @param value the double value to convert and pass
     */
    void bottleneckYSizeConversionToSlider(double value);
    /**
     * @brief Manages bottlenecks link between ui and model
     * @param value
     */
    void updateBottlenecks(double value);

private slots:
    void on_addBottleneckButton_clicked();

private:
    Ui::MainWindow *ui;
    // Bottleneck position spin box
    QDoubleSpinBox* bottleneckPositionSpinBox;
    // Bottleneck position slider
    QSlider* bottleneckPositionSlider;
    // Bottleneck X size slider
    QSlider* bottleneckXSizeSlider;
    // Bottleneck X size spin box
    QDoubleSpinBox* bottleneckXSizeSpinBox;
    // Bottleneck Y size slider
    QSlider* bottleneckYSizeSlider;
    // Bottleneck Y size spin box
    QDoubleSpinBox* bottleneckYSizeSpinBox;


    // TEMP
    QGroupBox* tempBottleneckGroupBox;
    QGridLayout* tempBottleneckGridLayout;
    QDoubleSpinBox* tempBottleneckPositionSpinBox;
    QSlider *tempBottleneckPositionSlider;
    QLabel *tempBottleneckPositionLabel;
    QDoubleSpinBox* tempBottleneckXSizeSpinBox;
    QSlider *tempBottleneckXSizeSlider;
    QLabel *tempBottleneckXSizeLabel;
    QDoubleSpinBox* tempBottleneckYSizeSpinBox;
    QSlider *tempBottleneckYSizeSlider;
    QLabel *tempBottleneckYSizeLabel;
};

#endif // MAINWINDOW_H
