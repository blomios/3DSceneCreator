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
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

        // Request an update
        update();
    }
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
}

void MainWidget::initTextures() {
    this->texture = new QOpenGLTexture(QImage(":/texture.png"));
}

void MainWidget::initShaders() {
    // Compiles the vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();
    // Compiles the fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();
    // Links shader pipeline
    if (!program.link())
        close();
    // Binds shader pipeline for use
    if (!program.bind())
        close();
}

GeometryEngine *MainWidget::getGeometries() const {
    return geometries;
}

void MainWidget::resizeGL(int w, int h) {
    // Computes the aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);
    // Sets near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;
    // Resets projection
    projection.setToIdentity();
    // Sets perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}

void MainWidget::paintGL() {
    // Clears color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -5.0);
    matrix.rotate(rotation);

    // Set modelview-projection matrix
    program.setUniformValue("mvp", projection * matrix);

    // Draws the skybox
    geometries->drawSkybox(&program);

    // Sets the texture
    this->texture->bind(0);
    program.setUniformValue("testTexture", 0);

    // Draws the model
    geometries->drawGeometry(&program);
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
    delete texture;
    texture = new QOpenGLTexture(QImage(path));
}
