#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <string>

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

    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_addBottleneckButton_clicked();
    void removeBottleneckButtonClicked();
    void on_textureButton_clicked();

private:
    Ui::MainWindow *ui;

    // Struct containing widgets to create the group boxes with bottleneck controls
    struct BottleneckControls {
        BottleneckControls() {
            tempBottleneckGroupBox = nullptr;
            tempBottleneckGridLayout = nullptr;
            tempBottleneckPositionSpinBox = nullptr;
            tempBottleneckPositionSlider = nullptr;
            tempBottleneckPositionLabel = nullptr;
            tempBottleneckXSizeSpinBox = nullptr;
            tempBottleneckXSizeSlider = nullptr;
            tempBottleneckXSizeLabel = nullptr;
            tempBottleneckYSizeSpinBox = nullptr;
            tempBottleneckYSizeSlider = nullptr;
            tempBottleneckYSizeLabel = nullptr;
        }
        int bottleNeckIndex;

        QGroupBox* tempBottleneckGroupBox;
        QGridLayout* tempBottleneckGridLayout;

        // Bottleneck position spin box
        QDoubleSpinBox* tempBottleneckPositionSpinBox;
        // Bottleneck position slider
        QSlider *tempBottleneckPositionSlider;
        // Bottleneck position label
        QLabel *tempBottleneckPositionLabel;

        // Bottleneck X size spin box
        QDoubleSpinBox* tempBottleneckXSizeSpinBox;
        // Bottleneck X size slider
        QSlider *tempBottleneckXSizeSlider;
        // Bottleneck X size label
        QLabel *tempBottleneckXSizeLabel;

        // Bottleneck Y size spin box
        QDoubleSpinBox* tempBottleneckYSizeSpinBox;
        // Bottleneck Y size slider
        QSlider *tempBottleneckYSizeSlider;
        // Bottleneck Y size label
        QLabel *tempBottleneckYSizeLabel;

        // Remove bottleneck button
        QPushButton *bottleneckRemovePushButton;
    };
    // Vector containing the bottlenecks control widgets
    std::vector<BottleneckControls> bottleneckWidgets;
};

#endif // MAINWINDOW_H
