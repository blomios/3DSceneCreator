#include "Camera.h"

bool Camera::isFreeCamera() const {
    return freeCamera;
}

Camera::Camera() {
    this->cameraPosition = QVector3D(0.0f, 0.0f, 0.0f);
    this->cameraUp = QVector3D(0.0f, 1.0f, 0.0f);
    this->cameraFront = QVector3D(0.0f, 0.0f, -1.0f);
    this->freeCamera = false;
    this->angularSpeed = 0;
}

Camera::~Camera() = default;

void Camera::keyPressEvent(QKeyEvent *e) {
    if (freeCamera) {
        float cameraSpeed = 0.05;
        if (e->key() == Qt::Key_Z) {
            this->cameraPosition += cameraSpeed * this->cameraFront;
        } else if (e->key() == Qt::Key_S) {
            this->cameraPosition -= cameraSpeed * this->cameraFront;
        } else if (e->key() == Qt::Key_D) {
            this->cameraPosition +=
                    QVector3D::crossProduct(this->cameraFront, this->cameraUp).normalized() * cameraSpeed;
        } else if (e->key() == Qt::Key_Q) {
            this->cameraPosition -=
                    QVector3D::crossProduct(this->cameraFront, this->cameraUp).normalized() * cameraSpeed;
        }
    }
}

void Camera::setFreeCam(bool freeCam) {
    this->freeCamera = freeCam;
}

void Camera::resetCamera() {
    this->cameraPosition = QVector3D();
    this->cameraFront = QVector3D();
    this->cameraUp = QVector3D();
    this->skyboxRotation = QQuaternion();
}

void Camera::mousePressEvent(QMouseEvent *e) {
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}

void Camera::mouseReleaseEvent(QMouseEvent *e) {
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}

void Camera::timerEvent(QTimerEvent *) {
    // Decrease angular speed (friction)
    angularSpeed *= 0.90;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;
        if (freeCamera) {
            skyboxRotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * skyboxRotation;
        }
    }
}

const QVector3D &Camera::getCameraPosition() const {
    return cameraPosition;
}

const QVector3D &Camera::getCameraFront() const {
    return cameraFront;
}

const QVector3D &Camera::getCameraUp() const {
    return cameraUp;
}

const QQuaternion &Camera::getRotation() const {
    return rotation;
}

const QQuaternion &Camera::getSkyboxRotation() const {
    return skyboxRotation;
}