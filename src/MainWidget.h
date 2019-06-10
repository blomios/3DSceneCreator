#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "GeometryEngine.h"
#include "Skybox.h"

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
    /**
     * Constructor
     * @param parent the parent widget(the main window)
     */
    explicit MainWidget(QWidget *parent = nullptr);

    /**
     * Destructor
     */
    ~MainWidget() override;

    /**
     * @return the geometry engine
     */
    GeometryEngine *getGeometries() const;

    /**
     * Updates the bottleneck's position and size, the bottleneck to update is identified with the provided index
     * @param index the bottleneck's index
     * @param position the new bottleneck's position
     * @param xSize the new bottleneck's X size
     * @param ySize the new bottleneck's Y size
     */
    void updateBottlenecks(int index, double position, double xSize, double ySize);

    /**
     * Adds a bottleneck with the provided attributes
     * @param position the position of the bottleneck
     * @param xSize the x size of the bottleneck
     * @param ySize the y size of the bottleneck
     */
    void addBottleneck(double position, double xSize, double ySize);

    /**
     * Removes the bottleneck identified by the provided index
     * @param index the bottleneck's index
     */
    void removeBottleneck(int index);

    /**
     * Sets the texture of the model
     * @param path the path to the texture
     */
    void setTexture(const QString& path);

    /**
     * Manages actions when a key is pressed
     * @param e the key event
     */
    void keyPressEvent(QKeyEvent *e) override;

    /**
     * Toggles the free camera
     * @param freeCam true if the free camera should be enabled; flase otherwise
     */
    void setFreeCam(bool freeCam);

    /**
     * Resets the camera position
     */
    void resetCamera();

public slots:
    /**
     * Sets the number of stages of the model
     * @param stages the number of stages
     */
    void setNbOfStages(int stages);

    /**
     * Sets the number of vertices per stages of the model
     * @param nbOfVerticesPerStage the number of vertices per stage
     */
    void setNbOfVerticesPerStage(int nbOfVerticesPerStage);

    /**
     * Sets the size of the cylinder of the model
     * @param size the size of the cylinder
     */
    void setCylinderSize(int size);

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

    /**
     * Event occurring every interval milliseconds
     * @param e the timer event
     */
    void timerEvent(QTimerEvent *e) override;

    /**
     * Initializes the main functions of the gl widget
     */
    void initializeGL() override;

    /**
     * Occurs when resizing
     * @param w
     * @param h
     */
    void resizeGL(int w, int h) override;

    void paintGL() override;

    void initShaders();

    void initTextures();

private:
    QBasicTimer timer;

    // Skybox
    Skybox* skybox;
    // Skybox shader program
    QOpenGLShaderProgram skyboxShaderProgram;

    // Model shader program
    QOpenGLShaderProgram modelShaderProgram;

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
};

#endif // MAINWIDGET_H
