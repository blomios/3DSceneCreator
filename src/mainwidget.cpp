#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
        QOpenGLWidget(parent),
        geometries(0),
        angularSpeed(0) {
}

MainWidget::~MainWidget() {
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete geometries;
    doneCurrent();
}

void MainWidget::mousePressEvent(QMouseEvent *e) {
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e) {
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

void MainWidget::timerEvent(QTimerEvent *) {
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
    // Request an update
    update();
}

void MainWidget::initializeGL() {
    // Initializes OpenGL function resolution for the current context
    initializeOpenGLFunctions();
    // Sets the clearing color to black
    glClearColor(0, 0, 0, 1);
    // Loads and initializes the shaders
    initShaders();
    // Initializes the textures
    initTextures();
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);
    // Enable back face culling
    glEnable(GL_CULL_FACE);
    // Initializes a model
    GeometryEngine::FigureData figure;
    figure.nbStages = 100;
    figure.nbVerticesPerStage = 100;
    figure.cylinderSize = 0;

    // Creates the geometry engine managing the model
    geometries = new GeometryEngine(figure);

    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);

    // Initializes camera vectors
    this->cameraPosition = QVector3D(0.0f, 0.0f, 0.0f);
    this->cameraUp = QVector3D(0.0f, 1.0f, 0.0f);
    this->cameraFront = QVector3D(0.0f, 0.0f, -1.0f);

    freeCamera = false;
}

void MainWidget::initTextures() {
    this->modelTexture = new QOpenGLTexture(QImage(":/texture.png"));

        // Faces list
        QOpenGLTexture::CubeMapFace cubeMapTarget[6] = {
                QOpenGLTexture::CubeMapNegativeX,
                QOpenGLTexture::CubeMapPositiveX,
                QOpenGLTexture::CubeMapNegativeY,
                QOpenGLTexture::CubeMapPositiveY,
                QOpenGLTexture::CubeMapNegativeZ,
                QOpenGLTexture::CubeMapPositiveZ
        };

        // Loads textures
        QImage skyboxImages[6];
        skyboxImages[0] = QImage(":/skybox/nx.png").convertToFormat(QImage::Format_RGBA8888);
        skyboxImages[1] = QImage(":/skybox/px.png").convertToFormat(QImage::Format_RGBA8888);
        skyboxImages[2] = QImage(":/skybox/ny.png").convertToFormat(QImage::Format_RGBA8888);
        skyboxImages[3] = QImage(":/skybox/py.png").convertToFormat(QImage::Format_RGBA8888);
        skyboxImages[4] = QImage(":/skybox/nz.png").convertToFormat(QImage::Format_RGBA8888);
        skyboxImages[5] = QImage(":/skybox/pz.png").convertToFormat(QImage::Format_RGBA8888);

        skyboxTexture = new QOpenGLTexture(QOpenGLTexture::TargetCubeMap);
        skyboxTexture->create();
        skyboxTexture->bind();
        skyboxTexture->setSize(skyboxImages[0].width(), skyboxImages[0].height(), skyboxImages[0].depth());
        skyboxTexture->setFormat(QOpenGLTexture::RGBAFormat);
        skyboxTexture->allocateStorage();
        skyboxTexture->setMinMagFilters(QOpenGLTexture::Nearest, QOpenGLTexture::Nearest);
        for (int i = 0; i < 6; i++) {
            uchar* bits = skyboxImages[i].bits();
            skyboxTexture->setData(0, 0, cubeMapTarget[i], QOpenGLTexture::RGBA, QOpenGLTexture::UInt8, bits, 0);
        }
        skyboxTexture->release();

}

void MainWidget::initShaders() {
    // Model shaders
    // Compiles the vertex shader
    if (!modelShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();
    // Compiles the fragment shader
    if (!modelShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();
    // Links shader pipeline
    if (!modelShaderProgram.link())
        close();

    // Skybox shaders
    // Compiles the vertex shader
    if (!skyboxShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/skybox/vshaderSkybox.glsl"))
        close();
    // Compiles the fragment shader
    if (!skyboxShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/skybox/fshaderSkybox.glsl"))
        close();
    // Links shader pipeline
    if (!skyboxShaderProgram.link())
        close();
}

GeometryEngine *MainWidget::getGeometries() const {
    return geometries;
}

void MainWidget::resizeGL(int w, int h) {
    // Computes the aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);
    // Sets near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 0.1f, zFar = 100.0, fov = 45.0;
    // Resets projection
    modelProjectionMatrix.setToIdentity();
    // Sets perspective projection
    modelProjectionMatrix.perspective(fov, aspect, zNear, zFar);
}

void MainWidget::paintGL() {
    // Clears color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Model matrix for the skybox
    QMatrix4x4 skyboxModelMatrix;
    skyboxModelMatrix.setToIdentity();
    skyboxModelMatrix.translate(0.0f, 0.0f, -5.0f);
    skyboxModelMatrix.scale(30);

    // View matrix for the skybox
    QMatrix4x4 skyboxViewMatrix;
    skyboxViewMatrix.setToIdentity();
    skyboxViewMatrix.lookAt(this->cameraPosition, this->cameraPosition + this->cameraFront, this->cameraUp);
    skyboxViewMatrix.rotate(skyboxRotation);

    // Projection matrix for the skybox
    QMatrix4x4 skyboxProjectionMatrix;
    skyboxProjectionMatrix = this->modelProjectionMatrix;

    // Sets the matrices in the shader program
    skyboxShaderProgram.bind();
    skyboxShaderProgram.setUniformValue("model", skyboxModelMatrix);
    skyboxShaderProgram.setUniformValue("view", skyboxViewMatrix);
    skyboxShaderProgram.setUniformValue("projection", skyboxProjectionMatrix);
    // Sets the texture in the model shader program
    this->skyboxTexture->bind(0);
    skyboxShaderProgram.setUniformValue("skyboxTexture", 0);
    skyboxShaderProgram.release();


    // Model matrix of the model
    QMatrix4x4 modelMatrix;
    modelMatrix.translate(0.0f, 0.0f, -5.0f);
    modelMatrix.rotate(rotation);

    // View matrix of the model
    QMatrix4x4 modelViewMatrix;
    modelViewMatrix.setToIdentity();
    modelViewMatrix.lookAt(this->cameraPosition, this->cameraPosition + this->cameraFront, this->cameraUp);

    // Projection of the model

    // Sets the matrices in the model shader program
    modelShaderProgram.bind();
    skyboxShaderProgram.setUniformValue("model", modelMatrix);
    skyboxShaderProgram.setUniformValue("view", modelViewMatrix);
    skyboxShaderProgram.setUniformValue("projection", modelProjectionMatrix);
    this->modelTexture->bind(0);
    modelShaderProgram.setUniformValue("modelTexture", 0);
    modelShaderProgram.release();

    // Draws the skybox
    skyboxShaderProgram.bind();
    glDepthMask(GL_FALSE);
    geometries->drawSkybox(&skyboxShaderProgram);
    glDepthMask(GL_TRUE);
    skyboxShaderProgram.release();

    // Draws the model
    modelShaderProgram.bind();
    geometries->drawGeometry(&modelShaderProgram);
    modelShaderProgram.release();
}

void MainWidget::setNbOfStages(int stages) {
    this->nbOfStages = stages;
    this->geometries->setNbOfStages(stages);
}

void MainWidget::setNbOfVerticesPerStage(int nbOfVerticesPerStage) {
    this->nbOfVerticesPerStage = nbOfVerticesPerStage;
    this->geometries->setNbOfVerticesPerStage(nbOfVerticesPerStage);
}

void MainWidget::updateBottlenecks(int index, double position, double xSize, double ySize) {
    if (position != -1 && xSize != -1 && ySize != -1) {
        this->geometries->updateBottleNeck(index, position, xSize, ySize);
    }
}

void MainWidget::addBottleneck(double position, double xSize, double ySize) {
    this->geometries->addBottleNeck(position, xSize, ySize);
}

void MainWidget::removeBottleneck(int index) {
    this->geometries->removeBottleNeck(index, true);
}

void MainWidget::setTexture(QString path) {
    delete modelTexture;
    modelTexture = new QOpenGLTexture(QImage(path));
}

void MainWidget::keyPressEvent(QKeyEvent *e) {
    if (freeCamera) {
        float cameraSpeed = 0.05;
        if (e->key() == Qt::Key_Z) {
            this->cameraPosition += cameraSpeed * this->cameraFront;
        } else if (e->key() == Qt::Key_S) {
            this->cameraPosition -= cameraSpeed * this->cameraFront;
        } else if (e->key() == Qt::Key_D) {
            this->cameraPosition += QVector3D::crossProduct(this->cameraFront, this->cameraUp).normalized() * cameraSpeed;
        } else if (e->key() == Qt::Key_Q) {
            this->cameraPosition -= QVector3D::crossProduct(this->cameraFront, this->cameraUp).normalized() * cameraSpeed;
        }
    }
}

void MainWidget::setFreeCam(bool freeCam) {
    this->freeCamera = freeCam;
}

void MainWidget::resetCamera() {
    this->cameraPosition = QVector3D();
    this->cameraFront = QVector3D();
    this->cameraUp = QVector3D();
    this->skyboxRotation = QQuaternion();
}
