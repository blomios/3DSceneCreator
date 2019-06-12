#include "GeometryEngine.h"

GeometryEngine::GeometryEngine(ChewToyModel *model, Skybox* skybox) {
    initializeOpenGLFunctions();

    this->model = model;
    this->skybox = skybox;
}

GeometryEngine::~GeometryEngine() {
    delete model;
}

//Draw the geometry
void GeometryEngine::drawGeometry(QOpenGLShaderProgram *program) {
    //this->model->placeVertices();
    // Binds the model's VBO and EBO
    this->model->bindVBO();
    this->model->bindEBO();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(ModelVertex));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int colorLocation = program->attributeLocation("color");
    program->enableAttributeArray(colorLocation);
    program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(ModelVertex));

    // Offset for texture coordinates
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int textureLocation = program->attributeLocation("texCoord");
    program->enableAttributeArray(textureLocation);
    program->setAttributeBuffer(textureLocation, GL_FLOAT, offset, 3, sizeof(ModelVertex));

    // Offset for texture coordinates
    offset += sizeof(QVector2D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int NormalsLocation = program->attributeLocation("normalsCoord");
    program->enableAttributeArray(NormalsLocation);
    program->setAttributeBuffer(NormalsLocation, GL_FLOAT, offset, 3, sizeof(ModelVertex));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLES, model->getIndicesNumber(), GL_UNSIGNED_SHORT, 0);

    // Releases the VBO and EBO
    this->model->releaseVBO();
    this->model->releaseEBO();
}

void GeometryEngine::drawSkybox(QOpenGLShaderProgram *program) {
    // Binds VBO
    skybox->bindVBO();
    // Offset for position
    quintptr offset = 0;
    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, 3 * sizeof(float));
    // Draws the skybox
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // Releases VBO
    skybox->releaseVBO();
}

void GeometryEngine::addBottleNeck(float yPos, float xSize, float ySize) {
    this->model->addBottleNeck(yPos, xSize, ySize);
}

void GeometryEngine::updateBottleNeck(int bnIndex, float yPos, float xSize, float ySize) {
    this->model->updateBottleNeck(bnIndex, yPos, xSize, ySize);
}

void GeometryEngine::removeBottleNeck(int bnIndex, bool deleteBnFromTheList) {
    this->model->removeBottleNeck(bnIndex, deleteBnFromTheList);
}

void GeometryEngine::setNbOfStages(int nbOfStages) {
    this->model->setNbOfStages(nbOfStages);
}

void GeometryEngine::setNbOfVerticesPerStage(int nbOfVerticesPerStage) {
    this->model->setNbOfVerticesPerStage(nbOfVerticesPerStage);
}

void GeometryEngine::setCylinderSize(float size) {
    this->model->setCylinderSize(size);
}
