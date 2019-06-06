#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QSlider>

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

    struct SkyboxVertexData {
        QVector3D position;
        QVector3D color;
        QVector3D texPosition;
    };

    struct BottleNeck
    {
        float yPos;
        float xSize;
        float ySize;
    };

    GeometryEngine();
    GeometryEngine(FigureData data);
    virtual ~GeometryEngine();

    void drawGeometry(QOpenGLShaderProgram *program);

    void addBottleNeck(float yPos, float xSize, float ySize);

    void updateBottleNeck(int bnIndex, float yPos, float xSize, float ySize);

    void removeBottleNeck(int bnIndex, bool deleteBnFromTheList);

    std::vector<BottleNeck> bottleNecks;

    void setNbOfStages(int nbOfStages);

    void setNbOfVerticesPerStage(int nbOfVerticesPerStage);

    // Initializes the skybox textures
    void initializeSkybox();

    // Draws the skybox
    void drawSkybox(QOpenGLShaderProgram *program);

private:

    void initGeometry();

    void placePointsOriginalPosition();

    int getStagesFromYPosition(float yPos);

    void setBottleNeck(float yPos, float xSize, float ySize);

    void setBuffers();

    FigureData figure;
    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;

    std::vector<VertexData> vertices;
    std::vector<GLushort> indices;



    int nbrVertices = 0;

    int nbrIndices = 0;

    // Skybox
    GLuint skyboxTextureId;
    std::vector<SkyboxVertexData> skyboxVertices;
    std::vector<GLushort> skyboxIndices;
    QOpenGLBuffer skyboxVerticesBuffer;
    QOpenGLBuffer skyboxIndicesBuffer;
};
#endif // GEOMETRYENGINE_H
