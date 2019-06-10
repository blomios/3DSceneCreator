#ifndef INC_3DSCENECREATOR_CHEWTOYMODEL_H
#define INC_3DSCENECREATOR_CHEWTOYMODEL_H


#include <QtGui/QOpenGLBuffer>
#include <QtGui/QVector2D>
#include <QtGui/QVector3D>
#include <cmath>

#define PI 3.14159265

class ChewToyModel {
public:

    struct VertexData {
        QVector3D position;
        QVector3D color;
        QVector2D texPosition;
    };

    ChewToyModel(int nbStage, int nbVertices, float cylinderSize);

    ~ChewToyModel();

    int getNbOfStages() const;

    int getNbOfVerticesPerStage() const;

    float getCylinderSize() const;

    void setNbOfVerticesPerStage(int nbOfVerticesPerStage);

    void setCylinderSize(float cylinderSize);

    void setNbOfStages(int nbOfStages);

    void placeVertices();

    void setBuffers();

    void updateBottleNeck(int bnIndex, float yPos, float xSize, float ySize);

    void addBottleNeck(float yPos, float xSize, float ySize);

    void setBottleNeck(float yPos, float xSize, float ySize);

    void removeBottleNeck(int bnIndex, bool deleteBnFromTheList);

    /**
     * Gets the closest stage from the y pos entered
     * @param yPos the y pos
     * @return the stage number
     */
    int getStagesFromYPosition(float yPos);

    void bindEBO();

    void bindVBO();

    void releaseVBO();

    void releaseEBO();

    int getIndicesNumber();

private:

    struct BottleNeck {
        float yPos;
        float xSize;
        float ySize;
    };
    // Number of vertices per stage
    int nbOfVerticesPerStage;
    // Size of the cylinder
    float cylinderSize;
    // Number of stages
    int nbOfStages;
    // VBO
    QOpenGLBuffer *modelVerticesBuffer;
    // EBO
    QOpenGLBuffer *modelIndicesBuffer;
    // Vertices of the model
    std::vector<VertexData> vertices;
    // Indices to build the model
    std::vector<GLushort> indices;
    // Bottlenecks of the model
    std::vector<BottleNeck> bottleNecks;


};


#endif //INC_3DSCENECREATOR_CHEWTOYMODEL_H
