#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "geometryengine.h"
#include "src/deprecated/Texture.h"

#include <math.h>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

class GeometryEngine;

class MainWidget : public QOpenGLWidget, protected QOpenGLFunctions {
Q_OBJECT

public:
    // Constructor
    explicit MainWidget(QWidget *parent = nullptr);

    // Destructor
    ~MainWidget() override;

    // Retrieves the geometry engine
    GeometryEngine *getGeometries() const;

    // Updates the bottleneck's position and size, the bottleneck to update is identified with the provided index
    void updateBottlenecks(int index, double position, double xSize, double ySize);

    // Adds a bottleneck with the provided position and size
    void addBottleneck(double position, double xSize, double ySize);

    // Removes the bottleneck identified by the provided index
    void removeBottleneck(int index);

    // Sets the texture of the model
    void setTexture(QString path);

public slots:
    // Sets the number of stages of the model
    void setNbOfStages(int stages);

    // Sets the number of vertices per stages of the model
    void setNbOfVerticesPerStage(int nbOfVerticesPerStage);

protected:
    void mousePressEvent(QMouseEvent *e) override;

    void mouseReleaseEvent(QMouseEvent *e) override;

    void timerEvent(QTimerEvent *e) override;

    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

    void initShaders();

    void initTextures();

private:
    QBasicTimer timer;
    QOpenGLShaderProgram program;
    GeometryEngine *geometries;

    QMatrix4x4 projection;

    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed;
    QQuaternion rotation;

    QOpenGLTexture* texture;

    // Object parameters
    int nbOfStages;
    int nbOfVerticesPerStage;
};

#endif // MAINWIDGET_H
