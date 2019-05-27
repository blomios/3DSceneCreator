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

    // Connects the sliders to the widget
    QObject::connect(nbOfStagesSlider, SIGNAL(valueChanged(int)), ui->GLWidget, SLOT(setNbOfStages(int)));
    QObject::connect(verticesPerStageSlider, SIGNAL(valueChanged(int)), ui->GLWidget, SLOT(setNbOfVerticesPerStage(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
