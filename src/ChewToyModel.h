#ifndef INC_3DSCENECREATOR_CHEWTOYMODEL_H
#define INC_3DSCENECREATOR_CHEWTOYMODEL_H


#include <QtGui/QOpenGLBuffer>
#include <QtGui/QVector2D>
#include <QtGui/QVector3D>
#include <cmath>
#include "ModelVertex.h"

#define PI 3.14159265

class ChewToyModel {
public:

    /**
     * Constructor
     * @param nbStage the number of stages of the model
     * @param nbVertices the number of vertices per stages
     * @param cylinderSize the size of the cylinder
     */
    ChewToyModel(int nbStage, int nbVertices, float cylinderSize);

    /**
     * Destructor
     */
    ~ChewToyModel();

    /**
     * Sets the number of vertices per stage
     * @param nbOfVerticesPerStage
     */
    void setNbOfVerticesPerStage(int nbOfVerticesPerStage);

    /**
     * Sets the cylinder size
     * @param cylinderSize
     */
    void setCylinderSize(float cylinderSize);

    /**
     * Sets the number of stages
     * @param nbOfStages
     */
    void setNbOfStages(int nbOfStages);

    /**
     * Places the model's vertices
     */
    void placeVertices();

    /**
     * Sets the VBO and VAO
     */
    void setBuffers();

    /**
     * Updates a bottleneck with the given parameters
     * @param bnIndex the bottleneck index in the vector
     * @param yPos the y position of the bottleneck
     * @param xSize the x size of the bottleneck
     * @param ySize the y size of the bottleneck
     */
    void updateBottleNeck(int bnIndex, float yPos, float xSize, float ySize);

    /**
     * Adds a bottleneck with the given parameters
     * @param yPos the y position of the bottleneck
     * @param xSize the x size of the bottleneck
     * @param ySize the y size of the bottleneck
     */
    void addBottleNeck(float yPos, float xSize, float ySize);

    void setBottleNeck(float yPos, float xSize, float ySize);

    /**
     * Removes a bottleneck
     * @param bnIndex the index of the bottleneck to remove
     * @param deleteBnFromTheList true if the bottleneck should be deleted from the bottleneck list
     */
    void removeBottleNeck(int bnIndex, bool deleteBnFromTheList);

    /**
     * Gets the closest stage from the y pos entered
     * @param yPos the y pos
     * @return the stage number
     */
    int getStagesFromYPosition(float yPos);

    /**
     * Binds the EBO
     */
    void bindEBO();

    /**
     * Binds the VBO
     */
    void bindVBO();

    /**
     * Releases the VBO
     */
    void releaseVBO();

    /**
     * Releases the EBO
     */
    void releaseEBO();

    /**
     * @return the number of indices in the EBO
     */
    int getIndicesNumber();

private:
    // Struct representing a bottleneck
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
    std::vector<ModelVertex> vertices;
    // Indices to build the model
    std::vector<GLushort> indices;
    // Bottlenecks of the model
    std::vector<BottleNeck> bottleNecks;
};


#endif //INC_3DSCENECREATOR_CHEWTOYMODEL_H
