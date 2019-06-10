#ifndef INC_3DSCENECREATOR_CAMERA_H
#define INC_3DSCENECREATOR_CAMERA_H


#include <QtGui/QVector3D>
#include <QtGui/QVector2D>
#include <QtGui/QQuaternion>
#include <QtGui/QKeyEvent>

class Camera {
private:
    QVector3D cameraPosition;
    QVector3D cameraFront;
    QVector3D cameraUp;
    bool freeCamera;
    QVector2D mousePressPosition;
    QQuaternion rotation;
    QQuaternion skyboxRotation;
    QVector3D rotationAxis;
    qreal angularSpeed;
public:
    Camera();

    ~Camera();

    void keyPressEvent(QKeyEvent *e);

    bool isFreeCamera() const;

    /**
     * Toggles the free camera
     * @param freeCam true if the free camera should be enabled; flase otherwise
     */
    void setFreeCam(bool freeCam);

    /**
     * Resets the camera position
     */
    void resetCamera();

    void mousePressEvent(QMouseEvent *e);

    void mouseReleaseEvent(QMouseEvent *e);

    void timerEvent(QTimerEvent *);

    const QVector3D &getCameraPosition() const;

    const QVector3D &getCameraFront() const;

    const QVector3D &getCameraUp() const;

    const QQuaternion &getRotation() const;

    const QQuaternion &getSkyboxRotation() const;
};


#endif //INC_3DSCENECREATOR_CAMERA_H
