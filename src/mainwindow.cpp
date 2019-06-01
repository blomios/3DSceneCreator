#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connects the spinboxes and the sliders together and also to the OpenGL widget
    // Number of stages
    QSlider* nbOfStagesSlider = ui->nbOfStagesSlider;
    QSpinBox* nbOfStagesSpinBox = ui->nbOfStagesSpinBox;
    QObject::connect(nbOfStagesSlider,  SIGNAL(valueChanged(int)), nbOfStagesSpinBox, SLOT(setValue(int)));
    QObject::connect(nbOfStagesSpinBox,  SIGNAL(valueChanged(int)), nbOfStagesSlider, SLOT(setValue(int)));
    QObject::connect(nbOfStagesSlider, SIGNAL(valueChanged(int)), ui->GLWidget, SLOT(setNbOfStages(int)));
    // Vertices per stage
    QSlider* verticesPerStageSlider = ui->verticesPerStageSlider;
    QSpinBox* verticesPerStageSpinBox = ui->verticesPerStageSpinBox;
    QObject::connect(verticesPerStageSlider, SIGNAL(valueChanged(int)), verticesPerStageSpinBox, SLOT(setValue(int)));
    QObject::connect(verticesPerStageSpinBox, SIGNAL(valueChanged(int)), verticesPerStageSlider, SLOT(setValue(int)));
    QObject::connect(verticesPerStageSlider, SIGNAL(valueChanged(int)), ui->GLWidget, SLOT(setNbOfVerticesPerStage(int)));
    // Bottleneck position
    this->bottleneckPositionSlider = ui->bottleneckPositionSlider;
    this->bottleneckPositionSpinBox = ui->bottleneckPositionDoubleSpinBox;
    QObject::connect(bottleneckPositionSlider, SIGNAL(valueChanged(int)), this, SLOT(bottleneckPositionConversionToSpinBox(int)));
    QObject::connect(bottleneckPositionSpinBox, SIGNAL(valueChanged(double)), this, SLOT(bottleneckPositionConversionToSlider(double)));
    // Bottleneck X-size
    this->bottleneckXSizeSlider = ui->bottleneckXSizeSlider;
    this->bottleneckXSizeSpinBox = ui->bottleneckXSizeDoubleSpinBox;
    QObject::connect(bottleneckXSizeSlider, SIGNAL(valueChanged(int)), this, SLOT(bottleneckXSizeConversionToSpinBox(int)));
    QObject::connect(bottleneckXSizeSpinBox, SIGNAL(valueChanged(double)), this, SLOT(bottleneckXSizeConversionToSlider(double)));
    // Bottleneck Y-size
    QSlider* bottleneckYSizeSlider = ui->bottleneckYSizeSlider;
    QDoubleSpinBox* bottleneckYSizeSpinBox = ui->bottleneckYSizeDoubleSpinBox;
    QObject::connect(bottleneckYSizeSlider, SIGNAL(valueChanged(int)), bottleneckYSizeSpinBox, SLOT(setValue(double)));
    QObject::connect(bottleneckYSizeSpinBox, SIGNAL(valueChanged(double)), bottleneckYSizeSlider, SLOT(setValue(int)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::bottleneckPositionConversionToSpinBox(int value) {
    this->bottleneckPositionSpinBox->setValue(static_cast<double>(value) / 10);
}

void MainWindow::bottleneckPositionConversionToSlider(double value) {
    this->bottleneckPositionSlider->setValue(static_cast<int>(value * 10));
}

void MainWindow::bottleneckXSizeConversionToSpinBox(int value) {
    this->bottleneckXSizeSpinBox->setValue(static_cast<double>(value) / 10);
}

void MainWindow::bottleneckXSizeConversionToSlider(double value) {
    this->bottleneckXSizeSlider->setValue(static_cast<int>(value * 10));
}
