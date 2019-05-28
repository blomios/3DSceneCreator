#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Retrieves the parameter sliders
    QSlider* nbOfStagesSlider = ui->nbOfStagesSlider;
    QSlider* verticesPerStageSlider = ui->verticesPerStageSlider;
    QSpinBox* nbOfStagesSpinBox = ui->nbOfStagesSpinBox;
    QSpinBox* verticesPerStageSpinBox = ui->verticesPerStageSpinBox;

    // Connects the sliders to the widget
    QObject::connect(nbOfStagesSlider, SIGNAL(valueChanged(int)), ui->GLWidget, SLOT(setNbOfStages(int)));
    QObject::connect(verticesPerStageSlider, SIGNAL(valueChanged(int)), ui->GLWidget, SLOT(setNbOfVerticesPerStage(int)));

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
