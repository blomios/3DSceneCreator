#include "ModelVertex.h"

ModelVertex::ModelVertex(QVector3D position, QVector3D color, QVector2D textCoords) {
    this->position = position;
    this->color = color;
    this->textureCoords = textCoords;
}

ModelVertex::ModelVertex() = default;

const QVector3D ModelVertex::getPosition() const {
    return position;
}

void ModelVertex::setPosition(const QVector3D &position) {
    ModelVertex::position = position;
}

const QVector3D &ModelVertex::getColor() const {
    return color;
}

void ModelVertex::setColor(const QVector3D &color) {
    ModelVertex::color = color;
}

const QVector2D &ModelVertex::getTextureCoords() const {
    return textureCoords;
}

void ModelVertex::setTextureCoords(const QVector2D &textureCoords) {
    ModelVertex::textureCoords = textureCoords;
}

void ModelVertex::setXPos(float x) {
    this->position.setX(x);
}

void ModelVertex::setYPos(float y) {
    this->position.setY(y);
}

void ModelVertex::setZPos(float z) {
    this->position.setZ(z);
}
