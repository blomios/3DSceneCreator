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

#define PI 3.14159265

class GeometryEngine : protected QOpenGLFunctions
{
public:
    struct FigureData
    {
        int nbVerticesPerStage;
        int nbStages;
        float cylinderSize;
    };

    struct VertexData
    {
        QVector3D position;
        QVector3D color;
        QVector2D texPosition;
    };
    struct BottleNeck
    {
        float yPos;
        float xSize;
        float ySize;
    };
    
    explicit GeometryEngine(FigureData data);

    virtual ~GeometryEngine();

    void drawGeometry(QOpenGLShaderProgram *program);

    void addBottleNeck(float yPos, float xSize, float ySize);

    void updateBottleNeck(int bnIndex, float yPos, float xSize, float ySize);

    void removeBottleNeck(int bnIndex, bool deleteBnFromTheList);

    std::vector<BottleNeck> bottleNecks;

    void setNbOfStages(int nbOfStages);

    void setNbOfVerticesPerStage(int nbOfVerticesPerStage);

    // Draws the skybox
    void drawSkybox(QOpenGLShaderProgram *program);

    void setCylinderSize(float size);

private:

    void initGeometry();

    void placePointsOriginalPosition();

    int getStagesFromYPosition(float yPos);

    void setBottleNeck(float yPos, float xSize, float ySize);

    void setBuffers();

    FigureData figure{};
    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;

    std::vector<VertexData> vertices;
    std::vector<GLushort> indices;



    int nbrVertices = 0;

    int nbrIndices = 0;

    // Skybox
    QOpenGLBuffer skyboxVerticesBuffer;
};
#endif // GEOMETRYENGINE_H
