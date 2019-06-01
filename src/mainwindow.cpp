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
    QObject::connect(bottleneckPositionSpinBox, SIGNAL(valueChanged(double)), this, SLOT(updateBottlenecks(double)));
    // Bottleneck X-size
    this->bottleneckXSizeSlider = ui->bottleneckXSizeSlider;
    this->bottleneckXSizeSpinBox = ui->bottleneckXSizeDoubleSpinBox;
    QObject::connect(bottleneckXSizeSlider, SIGNAL(valueChanged(int)), this, SLOT(bottleneckXSizeConversionToSpinBox(int)));
    QObject::connect(bottleneckXSizeSpinBox, SIGNAL(valueChanged(double)), this, SLOT(bottleneckXSizeConversionToSlider(double)));
    QObject::connect(bottleneckXSizeSpinBox, SIGNAL(valueChanged(double)), this, SLOT(updateBottlenecks(double)));
    // Bottleneck Y-size
    this->bottleneckYSizeSlider = ui->bottleneckYSizeSlider;
    this->bottleneckYSizeSpinBox = ui->bottleneckYSizeDoubleSpinBox;
    QObject::connect(bottleneckYSizeSlider, SIGNAL(valueChanged(int)), this, SLOT(bottleneckYSizeConversionToSpinBox(int)));
    QObject::connect(bottleneckYSizeSpinBox, SIGNAL(valueChanged(double)), this, SLOT(bottleneckYSizeConversionToSlider(double)));
    QObject::connect(bottleneckYSizeSpinBox, SIGNAL(valueChanged(double)), this, SLOT(updateBottlenecks(double)));
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

void MainWindow::bottleneckYSizeConversionToSpinBox(int value) {
    this->bottleneckYSizeSpinBox->setValue(static_cast<double>(value) / 10);
}

void MainWindow::bottleneckYSizeConversionToSlider(double value) {
    this->bottleneckYSizeSlider->setValue(static_cast<int>(value * 10));
}

void MainWindow::updateBottlenecks(double value) {
    if (sender() == bottleneckPositionSpinBox) {
        ui->GLWidget->updateBottlenecks(0, value, bottleneckXSizeSpinBox->value(), bottleneckYSizeSpinBox->value());
    } else if (sender() == bottleneckXSizeSpinBox) {
        ui->GLWidget->updateBottlenecks(0, bottleneckPositionSpinBox->value(), value, bottleneckYSizeSpinBox->value());
    } else if (sender() == bottleneckYSizeSpinBox) {
        ui->GLWidget->updateBottlenecks(0, bottleneckPositionSpinBox->value(), bottleneckXSizeSpinBox->value(), value);
    }
}

void MainWindow::on_addBottleneckButton_clicked() {
    this->tempBottleneckGroupBox = new QGroupBox("Bottleneck parameters");
    this->tempBottleneckGridLayout = new QGridLayout();
    this->tempBottleneckGroupBox->setLayout(tempBottleneckGridLayout);

    this->tempBottleneckPositionLabel = new QLabel("Position :");
    this->tempBottleneckGridLayout->addWidget(this->tempBottleneckPositionLabel, 0, 0);
    this->tempBottleneckPositionSlider = new QSlider(Qt::Horizontal);
    this->tempBottleneckPositionSlider->setRange(-5, 5);
    this->tempBottleneckGridLayout->addWidget(this->tempBottleneckPositionSlider, 1, 0);
    this->tempBottleneckPositionSpinBox = new QDoubleSpinBox();
    this->tempBottleneckPositionSpinBox->setRange(-0.5, 0.5);
    this->tempBottleneckPositionSpinBox->setSingleStep(0.1);
    this->tempBottleneckGridLayout->addWidget(this->tempBottleneckPositionSpinBox, 1, 1);

    this->tempBottleneckXSizeLabel = new QLabel("X-Size :");
    this->tempBottleneckGridLayout->addWidget(this->tempBottleneckXSizeLabel, 2, 0);
    this->tempBottleneckXSizeSlider = new QSlider(Qt::Horizontal);
    this->tempBottleneckXSizeSlider->setRange(-5, 5);
    this->tempBottleneckGridLayout->addWidget(this->tempBottleneckXSizeSlider, 3, 0);
    this->tempBottleneckXSizeSpinBox = new QDoubleSpinBox();
    this->tempBottleneckXSizeSpinBox->setRange(-0.5, 0.5);
    this->tempBottleneckXSizeSpinBox->setSingleStep(0.1);
    this->tempBottleneckGridLayout->addWidget(this->tempBottleneckXSizeSpinBox, 3, 1);

    this->tempBottleneckYSizeLabel = new QLabel("Y-Size :");
    this->tempBottleneckGridLayout->addWidget(this->tempBottleneckYSizeLabel, 4, 0);
    this->tempBottleneckYSizeSlider = new QSlider(Qt::Horizontal);
    this->tempBottleneckYSizeSlider->setRange(-5, 5);
    this->tempBottleneckGridLayout->addWidget(this->tempBottleneckYSizeSlider, 5, 0);
    this->tempBottleneckYSizeSpinBox = new QDoubleSpinBox();
    this->tempBottleneckXSizeSpinBox->setRange(-0.5, 0.5);
    this->tempBottleneckXSizeSpinBox->setSingleStep(0.1);
    this->tempBottleneckGridLayout->addWidget(this->tempBottleneckYSizeSpinBox, 5, 1);

    this->ui->scrollLayout->addWidget(tempBottleneckGroupBox);
}
