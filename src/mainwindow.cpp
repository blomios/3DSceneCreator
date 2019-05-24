#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Retrieves the two parameters
    QSlider* nbOfStagesSlider = ui->nbOfStagesSlider;
    QSlider* verticesPerStageSlider = ui->verticesPerStageSlider;
    ui->GLWidget->getGeometries()->setParametersSliders(nbOfStagesSlider, verticesPerStageSlider);
}

MainWindow::~MainWindow()
{
    delete ui;
}
