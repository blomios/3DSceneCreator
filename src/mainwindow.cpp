#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connects the spinboxes and the sliders together and connects them to the OpenGL widget
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
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::bottleneckPositionConversionToSpinBox(int value) {
    for (BottleneckControls bottleneckControls : this->bottleneckWidgets) {
        if (sender() == bottleneckControls.tempBottleneckPositionSlider) {
            bottleneckControls.tempBottleneckPositionSpinBox->setValue(static_cast<double>(value) / 10);
        }
    }
}

void MainWindow::bottleneckPositionConversionToSlider(double value) {
    for (BottleneckControls bottleneckControls : this->bottleneckWidgets) {
        if (sender() == bottleneckControls.tempBottleneckPositionSpinBox) {
            bottleneckControls.tempBottleneckPositionSlider->setValue(static_cast<int>(value * 10));
        }
    }
}

void MainWindow::bottleneckXSizeConversionToSpinBox(int value) {
    for (BottleneckControls bottleneckControls : this->bottleneckWidgets) {
        if (sender() == bottleneckControls.tempBottleneckXSizeSlider) {
            bottleneckControls.tempBottleneckXSizeSpinBox->setValue(static_cast<double>(value) / 10);
        }
    }
}

void MainWindow::bottleneckXSizeConversionToSlider(double value) {
    for (BottleneckControls bottleneckControls : this->bottleneckWidgets) {
        if (sender() == bottleneckControls.tempBottleneckXSizeSpinBox) {
            bottleneckControls.tempBottleneckXSizeSlider->setValue(static_cast<int>(value * 10));
        }
    }
}

void MainWindow::bottleneckYSizeConversionToSpinBox(int value) {
    for (BottleneckControls bottleneckControls : this->bottleneckWidgets) {
        if (sender() == bottleneckControls.tempBottleneckYSizeSlider) {
            bottleneckControls.tempBottleneckYSizeSpinBox->setValue(static_cast<double>(value) / 10);
        }
    }
}

void MainWindow::bottleneckYSizeConversionToSlider(double value) {
    for (BottleneckControls bottleneckControls : this->bottleneckWidgets) {
        if (sender() == bottleneckControls.tempBottleneckYSizeSpinBox) {
            bottleneckControls.tempBottleneckYSizeSlider->setValue(static_cast<int>(value * 10));
        }
    }
}

void MainWindow::updateBottlenecks(double value) {
    for (BottleneckControls bottleneckControls : this->bottleneckWidgets) {
        if (sender() == bottleneckControls.tempBottleneckPositionSpinBox) {
            ui->GLWidget->updateBottlenecks(bottleneckControls.bottleNeckIndex, value, bottleneckControls.tempBottleneckXSizeSpinBox->value(), bottleneckControls.tempBottleneckYSizeSpinBox->value());
        } else if (sender() == bottleneckControls.tempBottleneckXSizeSpinBox) {
            ui->GLWidget->updateBottlenecks(bottleneckControls.bottleNeckIndex, bottleneckControls.tempBottleneckPositionSpinBox->value(), value, bottleneckControls.tempBottleneckYSizeSpinBox->value());
        } else if (sender() == bottleneckControls.tempBottleneckYSizeSpinBox) {
            ui->GLWidget->updateBottlenecks(bottleneckControls.bottleNeckIndex, bottleneckControls.tempBottleneckPositionSpinBox->value(), bottleneckControls.tempBottleneckXSizeSpinBox->value(), value);
        }
    }
}

void MainWindow::on_addBottleneckButton_clicked() {
    BottleneckControls bottleneckControls;

    bottleneckControls.bottleNeckIndex = static_cast<int>(bottleneckWidgets.size());

    bottleneckControls.tempBottleneckGroupBox = new QGroupBox();
    bottleneckControls.tempBottleneckGroupBox->setTitle("Bottleneck #" + QString::number(this->bottleneckWidgets.size() + 1) + " parameters");
    bottleneckControls.tempBottleneckGridLayout = new QGridLayout();
    bottleneckControls.tempBottleneckGroupBox->setLayout(bottleneckControls.tempBottleneckGridLayout);

    bottleneckControls.tempBottleneckPositionLabel = new QLabel("Position :");
    bottleneckControls.tempBottleneckGridLayout->addWidget(bottleneckControls.tempBottleneckPositionLabel, 0, 0);
    bottleneckControls.tempBottleneckPositionSlider = new QSlider(Qt::Horizontal);
    bottleneckControls.tempBottleneckPositionSlider->setRange(-5, 5);
    bottleneckControls.tempBottleneckGridLayout->addWidget(bottleneckControls.tempBottleneckPositionSlider, 1, 0);
    bottleneckControls.tempBottleneckPositionSpinBox = new QDoubleSpinBox();
    bottleneckControls.tempBottleneckPositionSpinBox->setRange(-0.5, 0.5);
    bottleneckControls.tempBottleneckPositionSpinBox->setSingleStep(0.1);
    bottleneckControls.tempBottleneckGridLayout->addWidget(bottleneckControls.tempBottleneckPositionSpinBox, 1, 1);

    bottleneckControls.tempBottleneckXSizeLabel = new QLabel("X-Size :");
    bottleneckControls.tempBottleneckGridLayout->addWidget(bottleneckControls.tempBottleneckXSizeLabel, 2, 0);
    bottleneckControls.tempBottleneckXSizeSlider = new QSlider(Qt::Horizontal);
    bottleneckControls.tempBottleneckXSizeSlider->setRange(-5, 5);
    bottleneckControls.tempBottleneckGridLayout->addWidget(bottleneckControls.tempBottleneckXSizeSlider, 3, 0);
    bottleneckControls.tempBottleneckXSizeSpinBox = new QDoubleSpinBox();
    bottleneckControls.tempBottleneckXSizeSpinBox->setRange(-0.5, 0.5);
    bottleneckControls.tempBottleneckXSizeSpinBox->setSingleStep(0.1);
    bottleneckControls.tempBottleneckGridLayout->addWidget(bottleneckControls.tempBottleneckXSizeSpinBox, 3, 1);

    bottleneckControls.tempBottleneckYSizeLabel = new QLabel("Y-Size :");
    bottleneckControls.tempBottleneckGridLayout->addWidget(bottleneckControls.tempBottleneckYSizeLabel, 4, 0);
    bottleneckControls.tempBottleneckYSizeSlider = new QSlider(Qt::Horizontal);
    bottleneckControls.tempBottleneckYSizeSlider->setRange(-5, 5);
    bottleneckControls.tempBottleneckGridLayout->addWidget(bottleneckControls.tempBottleneckYSizeSlider, 5, 0);
    bottleneckControls.tempBottleneckYSizeSpinBox = new QDoubleSpinBox();
    bottleneckControls.tempBottleneckXSizeSpinBox->setRange(-0.5, 0.5);
    bottleneckControls.tempBottleneckXSizeSpinBox->setSingleStep(0.1);
    bottleneckControls.tempBottleneckGridLayout->addWidget(bottleneckControls.tempBottleneckYSizeSpinBox, 5, 1);

    this->bottleneckWidgets.push_back(bottleneckControls);

    // Links bottleneck position
    QObject::connect(bottleneckWidgets.at(bottleneckControls.bottleNeckIndex).tempBottleneckPositionSlider, SIGNAL(valueChanged(int)), this, SLOT(bottleneckPositionConversionToSpinBox(int)));
    QObject::connect(bottleneckWidgets.at(bottleneckControls.bottleNeckIndex).tempBottleneckPositionSpinBox, SIGNAL(valueChanged(double)), this, SLOT(bottleneckPositionConversionToSlider(double)));
    QObject::connect(bottleneckWidgets.at(bottleneckControls.bottleNeckIndex).tempBottleneckPositionSpinBox, SIGNAL(valueChanged(double)), this, SLOT(updateBottlenecks(double)));
    // Links bottleneck X-size
    QObject::connect(bottleneckWidgets.at(bottleneckControls.bottleNeckIndex).tempBottleneckXSizeSlider, SIGNAL(valueChanged(int)), this, SLOT(bottleneckXSizeConversionToSpinBox(int)));
    QObject::connect(bottleneckWidgets.at(bottleneckControls.bottleNeckIndex).tempBottleneckXSizeSpinBox, SIGNAL(valueChanged(double)), this, SLOT(bottleneckXSizeConversionToSlider(double)));
    QObject::connect(bottleneckWidgets.at(bottleneckControls.bottleNeckIndex).tempBottleneckXSizeSpinBox, SIGNAL(valueChanged(double)), this, SLOT(updateBottlenecks(double)));
    // Links bottleneck Y-size
    QObject::connect(bottleneckWidgets.at(bottleneckControls.bottleNeckIndex).tempBottleneckYSizeSlider, SIGNAL(valueChanged(int)), this, SLOT(bottleneckYSizeConversionToSpinBox(int)));
    QObject::connect(bottleneckWidgets.at(bottleneckControls.bottleNeckIndex).tempBottleneckYSizeSpinBox, SIGNAL(valueChanged(double)), this, SLOT(bottleneckYSizeConversionToSlider(double)));
    QObject::connect(bottleneckWidgets.at(bottleneckControls.bottleNeckIndex).tempBottleneckYSizeSpinBox, SIGNAL(valueChanged(double)), this, SLOT(updateBottlenecks(double)));

    this->ui->GLWidget->addBottleneck(0, 0, 0);

    this->ui->scrollLayout->addWidget(bottleneckControls.tempBottleneckGroupBox);
}
