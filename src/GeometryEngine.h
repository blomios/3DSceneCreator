#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QSlider>
#include <QVector2D>
#include <QVector3D>
#include <math.h>
#include "ChewToyModel.h"
#include "Skybox.h"

class GeometryEngine : protected QOpenGLFunctions {
public:

    explicit GeometryEngine(ChewToyModel *model, Skybox *skybox);

    virtual ~GeometryEngine();

    void drawGeometry(QOpenGLShaderProgram *program);

    void drawSkybox(QOpenGLShaderProgram *program);

    void addBottleNeck(float yPos, float xSize, float ySize);

    void updateBottleNeck(int bnIndex, float yPos, float xSize, float ySize);

    void removeBottleNeck(int bnIndex, bool deleteBnFromTheList);

    void setNbOfStages(int nbOfStages);

    void setNbOfVerticesPerStage(int nbOfVerticesPerStage);

    void setCylinderSize(float size);

private:
    ChewToyModel *model;
    Skybox *skybox;
};

#endif // GEOMETRYENGINE_H
