#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "geometryengine.h"

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

    /**
     * Manages actions when a key is pressed
     * @param e the key event
     */
    void keyPressEvent(QKeyEvent *e) override;

    void setFreeCam(bool freeCam);

    void resetCamera();

public slots:
    // Sets the number of stages of the model
    void setNbOfStages(int stages);

    // Sets the number of vertices per stages of the model
    void setNbOfVerticesPerStage(int nbOfVerticesPerStage);

protected:
    /**
     * Manages actions when a mouse button is pressed
     * @param e the mouse event
     */
    void mousePressEvent(QMouseEvent *e) override;

    /**
     * Manages actions when a mouse button is release
     * @param e the mouse event
     */
    void mouseReleaseEvent(QMouseEvent *e) override;

    void timerEvent(QTimerEvent *e) override;

    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

    void initShaders();

    void initTextures();

private:
    QBasicTimer timer;

    // Model shader program
    QOpenGLShaderProgram modelShaderProgram;
    // Skybox shader program
    QOpenGLShaderProgram skyboxShaderProgram;
    GeometryEngine *geometries;

    QMatrix4x4 modelProjectionMatrix;

    // Camera related
    QVector2D mousePressPosition;
    QQuaternion rotation;
    QQuaternion skyboxRotation;
    QVector3D rotationAxis;
    qreal angularSpeed;
    QVector3D cameraPosition;
    QVector3D cameraFront;
    QVector3D cameraUp;
    bool freeCamera;

    // Textures
    QOpenGLTexture* modelTexture;
    QOpenGLTexture *skyboxTexture;

    // Object parameters
    int nbOfStages;
    int nbOfVerticesPerStage;
};

#endif // MAINWIDGET_H
