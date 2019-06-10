#include "ChewToyModel.h"

ChewToyModel::ChewToyModel(int nbStage, int nbVertices, float cylinderSize) {
    this->nbOfStages = nbStage;
    this->nbOfVerticesPerStage = nbVertices;
    this->cylinderSize = cylinderSize;

    // Creates the VBO for the chew toy model
    this->modelVerticesBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    modelVerticesBuffer->create();

    // Creates the EBO for the chew toy model
    this->modelIndicesBuffer = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    modelIndicesBuffer->create();

    placeVertices();
}

ChewToyModel::~ChewToyModel() {
    delete this->modelVerticesBuffer;
    delete this->modelIndicesBuffer;
}

int ChewToyModel::getNbOfStages() const {
    return nbOfStages;
}

int ChewToyModel::getNbOfVerticesPerStage() const {
    return nbOfVerticesPerStage;
}

float ChewToyModel::getCylinderSize() const {
    return cylinderSize;
}

void ChewToyModel::setNbOfVerticesPerStage(int nbOfVerticesPerStage) {
    vertices.clear();
    indices.clear();
    modelVerticesBuffer->destroy();
    modelIndicesBuffer->destroy();
    this->nbOfVerticesPerStage = nbOfVerticesPerStage;
    modelVerticesBuffer->create();
    modelIndicesBuffer->create();
    placeVertices();
    for (auto &bottleNeck : bottleNecks) {
        setBottleNeck(bottleNeck.yPos, bottleNeck.xSize, bottleNeck.ySize);
    }
}

void ChewToyModel::setCylinderSize(float cylinderSize) {
    vertices.clear();
    indices.clear();
    modelVerticesBuffer->destroy();
    modelIndicesBuffer->destroy();
    this->cylinderSize = cylinderSize / 10;
    modelVerticesBuffer->create();
    modelIndicesBuffer->create();
    placeVertices();
}

void ChewToyModel::setNbOfStages(int nbOfStages) {
    vertices.clear();
    indices.clear();
    modelVerticesBuffer->destroy();
    modelIndicesBuffer->destroy();
    this->nbOfStages = nbOfStages;
    modelVerticesBuffer->create();
    modelIndicesBuffer->create();
    placeVertices();
    for (auto &bottleNeck : bottleNecks) {
        setBottleNeck(bottleNeck.yPos, bottleNeck.xSize, bottleNeck.ySize);
    }
}

void ChewToyModel::placeVertices() {
    float P = this->cylinderSize * 100 / (1 + this->cylinderSize);
    int N = P * this->nbOfStages / 100;
    int beginStage = 0;
    int maxStage = (this->nbOfStages - N) / 2;
    //Set position of each vertices
    for (int i = beginStage; i <= maxStage; i++) {
        for (int j = 0; j < this->nbOfVerticesPerStage; j++) {

            float x = cos(((2 * PI) / this->nbOfVerticesPerStage) * j) * sin((PI / (this->nbOfStages)) * i);
            float y = cos((PI / (this->nbOfStages)) * i);
            float z = sin(((2 * PI) / this->nbOfVerticesPerStage) * j) * sin((PI / (this->nbOfStages)) * i);

            QVector3D color = QVector3D(1.0f, abs(x), 0.0f); //Set a color with a nice gradient color :p
            QVector2D texCoords = QVector2D((float) j / this->nbOfVerticesPerStage,
                                            (float) i / maxStage);

            //Add the created vertice in the tab
            VertexData vertex = {QVector3D(x, y, z), color, texCoords};

            vertices.push_back(vertex);
        }
    }

    //Set position of each vertices
    beginStage = (this->nbOfStages - N) / 2 + 1;
    maxStage = (this->nbOfStages - N) / 2 + N;
    for (int i = beginStage; i <= maxStage; i++) {

        for (int j = 0; j < this->nbOfVerticesPerStage; j++) {

            float x = cos(((2 * PI) / this->nbOfVerticesPerStage) * j) *
                      sin((PI / (this->nbOfStages)) * ((this->nbOfStages - N) / 2));
            float y = cos((PI / (this->nbOfStages)) * i);
            float z = sin(((2 * PI) / this->nbOfVerticesPerStage) * j) *
                      sin((PI / (this->nbOfStages)) * ((this->nbOfStages - N) / 2));

            QVector3D color = QVector3D(1.0f, abs(x), 0.0f); //Set a color with a nice gradient color :p
            QVector2D texCoords = QVector2D((float) j / this->nbOfVerticesPerStage,
                                            (float) i / maxStage);

            //Add the created vertice in the tab
            VertexData vertex = {QVector3D(x, y, z), color, texCoords};

            vertices.push_back(vertex);
        }
    }

    //Set position of each vertices
    beginStage = (this->nbOfStages - N) / 2 + N + 1;
    maxStage = this->nbOfStages;
    for (int i = beginStage; i <= maxStage; i++) {

        for (int j = 0; j < this->nbOfVerticesPerStage; j++) {

            float x = cos(((2 * PI) / this->nbOfVerticesPerStage) * j) * sin((PI / (this->nbOfStages)) * i);
            float y = cos((PI / (this->nbOfStages)) * i);
            float z = sin(((2 * PI) / this->nbOfVerticesPerStage) * j) * sin((PI / (this->nbOfStages)) * i);

            QVector3D color = QVector3D(1.0f, abs(x), 0.0f); //Set a color with a nice gradient color :p
            QVector2D texCoords = QVector2D((float) j / this->nbOfVerticesPerStage,
                                            (float) i / maxStage);

            //Add the created vertice in the tab
            VertexData vertex = {QVector3D(x, y, z), color, texCoords};

            vertices.push_back(vertex);
        }
    }


    //Set indices tab (link the vertices of stage N withe the vertices of stage N+1 to create faces) don't touch it is working... I think
    for (int i = 1; i <= this->nbOfStages; i++) {
        for (int j = 0; j < this->nbOfVerticesPerStage; j++) {

            std::vector<GLushort> arr = {
            };

            arr.push_back(this->nbOfVerticesPerStage * i + j);
            arr.push_back(this->nbOfVerticesPerStage * (i - 1) + j);
            arr.push_back(this->nbOfVerticesPerStage * (i) + ((j + 1) % this->nbOfVerticesPerStage));

            arr.push_back(this->nbOfVerticesPerStage * (i - 1) + j);
            arr.push_back(this->nbOfVerticesPerStage * (i - 1) + ((j + 1) % this->nbOfVerticesPerStage));
            arr.push_back(this->nbOfVerticesPerStage * (i) + ((j + 1) % this->nbOfVerticesPerStage));

            for (int j = 0; j < arr.size(); j++) {
                indices.push_back(arr[j]);
            }

        }
    }

    setBuffers();
}

void ChewToyModel::setBuffers() {

    // Sets the VBO
    auto *arr = new VertexData[vertices.size()];
    copy(vertices.begin(), vertices.end(), arr);
    modelVerticesBuffer->bind();
    modelVerticesBuffer->allocate(arr, vertices.size() * sizeof(VertexData));
    modelVerticesBuffer->release();
    delete[] arr;

    // Sets the EBO
    auto *arrIndices = new GLushort[indices.size()];
    copy(indices.begin(), indices.end(), arrIndices);
    modelIndicesBuffer->bind();
    modelIndicesBuffer->allocate(arrIndices, indices.size() * sizeof(GLushort));
    modelIndicesBuffer->release();
    delete[] arrIndices;

}

void ChewToyModel::removeBottleNeck(int bnIndex, bool deleteBnFromTheList) {

    float yPos = bottleNecks[bnIndex].yPos;
    float xSize = bottleNecks[bnIndex].xSize;
    float ySize = bottleNecks[bnIndex].ySize;

    int initialIndex = getStagesFromYPosition(yPos) - nbOfVerticesPerStage / 2;

    int index = 0;

    float coeff = xSize;

    while (initialIndex + index < vertices.size() && initialIndex - index >= 0 &&
           abs(vertices[initialIndex + index].position.y() - yPos) < ySize) {

        float coeffSec = 1 - coeff * cos((PI / 2 / ySize) * abs(vertices[initialIndex + index].position.y() - yPos));

        //qDebug() << cos((PI/2/ySize) * abs(vertices[initialIndex + index].position.y() - yPos));
        if (index == 0) {
            vertices[initialIndex + index].position.setZ(vertices[initialIndex + index].position.z() / (coeffSec));
            vertices[initialIndex + index].position.setX(vertices[initialIndex + index].position.x() / (coeffSec));

        } else {
            vertices[initialIndex + index].position.setZ(vertices[initialIndex + index].position.z() / (coeffSec));
            vertices[initialIndex - index].position.setZ(vertices[initialIndex - index].position.z() / (coeffSec));

            vertices[initialIndex + index].position.setX(vertices[initialIndex + index].position.x() / (coeffSec));
            vertices[initialIndex - index].position.setX(vertices[initialIndex - index].position.x() / (coeffSec));
        }


        index++;

    }

    modelVerticesBuffer->destroy();
    modelIndicesBuffer->destroy();

    modelVerticesBuffer->create();
    modelIndicesBuffer->create();

    setBuffers();

    if (deleteBnFromTheList)
        bottleNecks.erase(bottleNecks.begin() + bnIndex);

}

void ChewToyModel::updateBottleNeck(int bnIndex, float yPos, float xSize, float ySize) {

    removeBottleNeck(bnIndex, false);

    setBottleNeck(yPos, xSize, ySize);

    bottleNecks[bnIndex] = {yPos, xSize, ySize};


}

void ChewToyModel::addBottleNeck(float yPos, float xSize, float ySize) {
    BottleNeck bn = {yPos, xSize, ySize};

    bottleNecks.push_back(bn);


    setBottleNeck(yPos, xSize, ySize);

}

void ChewToyModel::setBottleNeck(float yPos, float xSize, float ySize) {

    int initialIndex = getStagesFromYPosition(yPos) - nbOfVerticesPerStage / 2;


    int index = 0;

    float coeff = xSize;

    while (initialIndex + index < vertices.size() && initialIndex - index >= 0 &&
           abs(vertices[initialIndex + index].position.y() - yPos) < ySize) {


        float coeffSec = 1 - coeff * cos((PI / 2 / ySize) * abs(vertices[initialIndex + index].position.y() - yPos));

        //qDebug() << cos((PI/2/ySize) * abs(vertices[initialIndex + index].position.y() - yPos));

        if (index == 0) {
            vertices[initialIndex + index].position.setZ(vertices[initialIndex + index].position.z() * (coeffSec));
            vertices[initialIndex + index].position.setX(vertices[initialIndex + index].position.x() * (coeffSec));
        } else {
            vertices[initialIndex + index].position.setZ(vertices[initialIndex + index].position.z() * (coeffSec));
            vertices[initialIndex - index].position.setZ(vertices[initialIndex - index].position.z() * (coeffSec));

            vertices[initialIndex + index].position.setX(vertices[initialIndex + index].position.x() * (coeffSec));
            vertices[initialIndex - index].position.setX(vertices[initialIndex - index].position.x() * (coeffSec));
        }

        index++;

    }

    modelVerticesBuffer->destroy();
    modelIndicesBuffer->destroy();

    modelVerticesBuffer->create();
    modelIndicesBuffer->create();

    setBuffers();
}


int ChewToyModel::getStagesFromYPosition(float yPos) {

    int lastIndex = 0;

    for (int i = nbOfVerticesPerStage; i < vertices.size(); i += nbOfVerticesPerStage) {

        // qDebug() << vertices[i].position.y();

        if (abs(vertices[i].position.y() - yPos) > abs(vertices[lastIndex].position.y() - yPos)) {

            return lastIndex;
        } else {
            lastIndex = i;
        }

    }
}

void ChewToyModel::bindEBO() {
    this->modelIndicesBuffer->bind();
}

void ChewToyModel::releaseEBO() {
    this->modelIndicesBuffer->release();
}

void ChewToyModel::bindVBO() {
    this->modelVerticesBuffer->bind();
}

void ChewToyModel::releaseVBO() {
    this->modelVerticesBuffer->release();
}

int ChewToyModel::getIndicesNumber() {
    return this->indices.size();
}

