#include "MainWidget.h"

MainWidget::MainWidget(QWidget *parent) : QOpenGLWidget(parent) {}

MainWidget::~MainWidget() {
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete geometries;
    delete skybox;
    doneCurrent();
}

void MainWidget::mousePressEvent(QMouseEvent *e) {
    this->camera->mousePressEvent(e);
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e) {
    this->camera->mouseReleaseEvent(e);
}

void MainWidget::timerEvent(QTimerEvent *) {
    this->camera->timerEvent(nullptr);
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
    this->skybox = new Skybox();
    initTextures();
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);
    // Enable back face culling
    glEnable(GL_CULL_FACE);
    // Creates the geometry engine managing the model
    this->geometries = new GeometryEngine(new ChewToyModel(70, 70, 1), skybox);

    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);

    // Initializes camera
    this->camera = new Camera();
}

void MainWidget::initTextures() {
    this->modelTexture = new QOpenGLTexture(QImage(":/texture.png"));
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
    skyboxViewMatrix.lookAt(camera->getCameraPosition(), camera->getCameraPosition() + camera->getCameraFront(), camera->getCameraUp());
    skyboxViewMatrix.rotate(camera->getSkyboxRotation());

    // Projection matrix for the skybox
    QMatrix4x4 skyboxProjectionMatrix;
    skyboxProjectionMatrix = this->modelProjectionMatrix;

    // Sets the matrices in the shader program
    skyboxShaderProgram.bind();
    skyboxShaderProgram.setUniformValue("model", skyboxModelMatrix);
    skyboxShaderProgram.setUniformValue("view", skyboxViewMatrix);
    skyboxShaderProgram.setUniformValue("projection", skyboxProjectionMatrix);
    // Sets the texture in the model shader program
    skyboxShaderProgram.setUniformValue("skyboxTexture", 0);
    skyboxShaderProgram.release();


    // Model matrix of the model
    QMatrix4x4 modelMatrix;
    modelMatrix.translate(0.0f, 0.0f, -5.0f);
    modelMatrix.rotate(camera->getRotation());

    // View matrix of the model
    QMatrix4x4 modelViewMatrix;
    modelViewMatrix.setToIdentity();
    modelViewMatrix.lookAt(camera->getCameraPosition(), camera->getCameraPosition() + camera->getCameraFront(), camera->getCameraUp());

    // Projection of the model

    // Light position
    QVector3D lightPosition = skyboxViewMatrix * skyboxModelMatrix * QVector3D(-1, 0.5, -1);

    // Sets the matrices in the model shader program
    modelShaderProgram.bind();
    modelShaderProgram.setUniformValue("model", modelMatrix);
    modelShaderProgram.setUniformValue("view", modelViewMatrix);
    modelShaderProgram.setUniformValue("projection", modelProjectionMatrix);
    modelShaderProgram.setUniformValue("modelTexture", 0);
    modelShaderProgram.setUniformValue("viewPos", modelViewMatrix);
    modelShaderProgram.setUniformValue("lightPos", lightPosition);
    modelShaderProgram.release();

    // Draws the skybox
    skyboxShaderProgram.bind();
    this->skybox->bindTexture();
    glDepthMask(GL_FALSE);
    geometries->drawSkybox(&skyboxShaderProgram);
    glDepthMask(GL_TRUE);
    this->skybox->releaseTexture();
    skyboxShaderProgram.release();

    // Draws the model
    modelShaderProgram.bind();
    this->modelTexture->bind(0);
    geometries->drawGeometry(&modelShaderProgram);
    this->modelTexture->release(0);
    modelShaderProgram.release();
}

void MainWidget::setNbOfStages(int stages) {
    this->geometries->setNbOfStages(stages);
}

void MainWidget::setNbOfVerticesPerStage(int nbOfVerticesPerStage) {
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

void MainWidget::setCylinderSize(int size) {
    this->geometries->setCylinderSize(size);
}

void MainWidget::setTexture(const QString& path) {
    QImage image = QImage(path);
    if (!image.isNull()) {
        delete modelTexture;
        modelTexture = new QOpenGLTexture(image);
    }
}

Camera *MainWidget::getCamera() const {
    return camera;
}
