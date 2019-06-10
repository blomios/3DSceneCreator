#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <string>
#include <QtWidgets/QRadioButton>
#include <QApplication>
#include <QLabel>
#include <QSurfaceFormat>

#include "MainWidget.h"
#include "ui_mainwindow.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
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

    /**
     * Sends the key press event to the gl widget
     * @param event the QKeyEvent containing the event data
     */
    void keyPressEvent(QKeyEvent *event);

    /**
     * Manages the camera radio buttons, enabling one and disabling the other
     */
    void cameraButtonManagement();

private slots:

    /**
     * Triggered when the "Add a bottleneck" button is clicked
     * Creates the dedicated UI section for the new bottleneck with the needed buttons
     * Also calls the GL widget to create a new bottleneck
     */
    void on_addBottleneckButton_clicked();

    /**
     * Triggered when the "Remove the bottleneck" button is clicked
     * Calls the gl widget to remove the bottleneck
     * Deletes the bottleneck dedicated UI section
     */
    void removeBottleneckButtonClicked();

    /**
     * Triggered when the "Change texture" button is clicked
     * Opens a dialog to load the texture file
     */
    void on_textureButton_clicked();

    /**
     * Triggered when the "Reset camera position" button is clicked
     * Calls the GL widget to reset the camera position
     */
    void on_resetCameraButton_clicked();

private:
    // The UI element containing every component
    Ui::MainWindow *ui;

    // Struct containing every widget necessary to create the group boxes with the bottleneck controls
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
            bottleneckRemovePushButton = nullptr;
            bottleNeckIndex = 0;
        }

        int bottleNeckIndex;

        QGroupBox *tempBottleneckGroupBox;
        QGridLayout *tempBottleneckGridLayout;

        // Bottleneck position spin box
        QDoubleSpinBox *tempBottleneckPositionSpinBox;
        // Bottleneck position slider
        QSlider *tempBottleneckPositionSlider;
        // Bottleneck position label
        QLabel *tempBottleneckPositionLabel;

        // Bottleneck X size spin box
        QDoubleSpinBox *tempBottleneckXSizeSpinBox;
        // Bottleneck X size slider
        QSlider *tempBottleneckXSizeSlider;
        // Bottleneck X size label
        QLabel *tempBottleneckXSizeLabel;

        // Bottleneck Y size spin box
        QDoubleSpinBox *tempBottleneckYSizeSpinBox;
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
