#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    QSpinBox* nbOfStagesSpinBox = ui->nbOfStagesSpinBox;
    QSpinBox* verticesPerStageSpinBox = ui->verticesPerStageSpinBox;

    // Connects the sliders to the widget
    QObject::connect(nbOfStagesSlider, SIGNAL(valueChanged(int)), ui->GLWidget, SLOT(setNbOfStages(int)));
    QObject::connect(verticesPerStageSlider, SIGNAL(valueChanged(int)), ui->GLWidget, SLOT(setNbOfVerticesPerStage(int)));
    // Bottleneck position
    QSlider* bottleneckPositionSlider = ui->bottleneckPositionSlider;
    QDoubleSpinBox* bottleneckPositionSpinBox = ui->bottleneckPositionDoubleSpinBox;
    QObject::connect(bottleneckPositionSlider, SIGNAL(valueChanged(int)), bottleneckPositionSpinBox, SLOT(setValue(double)));
    QObject::connect(bottleneckPositionSpinBox, SIGNAL(valueChanged(double)), bottleneckPositionSlider, SLOT(setValue(int)));
    // Bottleneck X-size
    QSlider* bottleneckXSizeSlider = ui->bottleneckXSizeSlider;
    QDoubleSpinBox* bottleneckXSizeSpinBox = ui->bottleneckXSizeDoubleSpinBox;
    QObject::connect(bottleneckXSizeSlider, SIGNAL(static_cast<double>(valueChanged(int))), bottleneckXSizeSpinBox, SLOT(setValue(double)));
    QObject::connect(bottleneckXSizeSpinBox, SIGNAL(valueChanged(double)), bottleneckXSizeSlider, SLOT(setValue(int)));
    // Bottleneck Y-size
    QSlider* bottleneckYSizeSlider = ui->bottleneckYSizeSlider;
    QDoubleSpinBox* bottleneckYSizeSpinBox = ui->bottleneckYSizeDoubleSpinBox;
    QObject::connect(bottleneckYSizeSlider, SIGNAL(valueChanged(int)), bottleneckYSizeSpinBox, SLOT(setValue(double)));
    QObject::connect(bottleneckYSizeSpinBox, SIGNAL(valueChanged(double)), bottleneckYSizeSlider, SLOT(setValue(int)));

    // Connects the spinboxes and the sliders together
    QObject::connect(nbOfStagesSlider,  SIGNAL(valueChanged(int)), nbOfStagesSpinBox, SLOT(setValue(int)));
    QObject::connect(nbOfStagesSpinBox,  SIGNAL(valueChanged(int)), nbOfStagesSlider, SLOT(setValue(int)));
    QObject::connect(verticesPerStageSlider, SIGNAL(valueChanged(int)), verticesPerStageSpinBox, SLOT(setValue(int)));
    QObject::connect(verticesPerStageSpinBox, SIGNAL(valueChanged(int)), verticesPerStageSlider, SLOT(setValue(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
