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

    for(int i=0; i<bottleNecks.size(); i++){
        removeBottleNeck(i, false);
    }

    vertices.clear();
    indices.clear();
    modelVerticesBuffer->destroy();
    modelIndicesBuffer->destroy();
    this->cylinderSize = cylinderSize / 10;
    modelVerticesBuffer->create();
    modelIndicesBuffer->create();
    placeVertices();

    for(int i=0; i<bottleNecks.size(); i++){
        setBottleNeck(bottleNecks[i].yPos, bottleNecks[i].xSize, bottleNecks[i].ySize);
    }
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


    QVector3D sphereCenterUp = QVector3D(0, cylinderSize/2, 0);
    QVector3D sphereCenterDown = QVector3D(0, -cylinderSize/2, 0);

    //Set position of each vertices
    for (int i = beginStage; i <= maxStage; i++) {
        for (int j = 0; j < this->nbOfVerticesPerStage; j++) {

            float x = cos(((2 * PI) / this->nbOfVerticesPerStage) * j) * sin((PI / (this->nbOfStages)) * i);
            float y = cos((PI / (this->nbOfStages)) * i);
            float z = sin(((2 * PI) / this->nbOfVerticesPerStage) * j) * sin((PI / (this->nbOfStages)) * i);

            QVector3D color = QVector3D(1.0f, abs(x), 0.0f); //Set a color with a nice gradient color :p
            QVector2D texCoords = QVector2D((float) j / this->nbOfVerticesPerStage,
                                            (float) i / maxStage);
            QVector3D pos(x, y, z);
            QVector3D normalCoord = pos - sphereCenterUp;

            //Add the created vertice in the tab
            ModelVertex vertex(pos, color, texCoords, normalCoord);

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
                                            (float) i / nbOfStages);

            QVector3D pos(x, y, z);
            QVector3D normalCoord = pos - QVector3D(0, y, 0);

            //Add the created vertice in the tab
            ModelVertex vertex(QVector3D(x, y, z), color, texCoords,normalCoord);

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
                                            (float) i / nbOfStages);

            QVector3D pos(x, y, z);
            QVector3D normalCoord = pos - sphereCenterDown;

            //Add the created vertice in the tab
            ModelVertex vertex(QVector3D(x, y, z), color, texCoords,normalCoord);

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

            for (unsigned short k : arr) {
                indices.push_back(k);
            }

        }
    }

    setBuffers();
}

void ChewToyModel::setBuffers() {

    // Sets the VBO
    auto *arr = new ModelVertex[vertices.size()];
    copy(vertices.begin(), vertices.end(), arr);
    modelVerticesBuffer->bind();
    modelVerticesBuffer->allocate(arr, vertices.size() * sizeof(ModelVertex));
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

    int initialIndex = getStagesFromYPosition(yPos) + nbOfVerticesPerStage / 2;

    int index = 0;

    float coeff = xSize;

    while (initialIndex + index < vertices.size() && initialIndex - index >= 0 &&
           abs(vertices[initialIndex + index].getPosition().y() - yPos) < ySize) {

        float coeffSec = 1 - coeff * cos((PI / 2 / ySize) * abs(vertices[initialIndex + index].getPosition().y() - yPos));

        //qDebug() << cos((PI/2/ySize) * abs(vertices[initialIndex + index].position.y() - yPos));
        if (index == 0) {
            vertices[initialIndex + index].setZPos(vertices[initialIndex + index].getPosition().z() / (coeffSec));
            vertices[initialIndex + index].setXPos(vertices[initialIndex + index].getPosition().x() / (coeffSec));

        } else {
            vertices[initialIndex + index].setZPos(vertices[initialIndex + index].getPosition().z() / (coeffSec));
            vertices[initialIndex - index].setZPos(vertices[initialIndex - index].getPosition().z() / (coeffSec));

            vertices[initialIndex + index].setXPos(vertices[initialIndex + index].getPosition().x() / (coeffSec));
            vertices[initialIndex - index].setXPos(vertices[initialIndex - index].getPosition().x() / (coeffSec));
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

    int initialIndex = getStagesFromYPosition(yPos) + nbOfVerticesPerStage / 2;


    int index = 0;

    float coeff = xSize;

    while (initialIndex + index < vertices.size() && initialIndex - index >= 0 &&
           abs(vertices[initialIndex + index].getPosition().y() - yPos) < ySize) {


        float coeffSec = 1 - coeff * cos((PI / 2 / ySize) * abs(vertices[initialIndex + index].getPosition().y() - yPos));

        //qDebug() << cos((PI/2/ySize) * abs(vertices[initialIndex + index].position.y() - yPos));

        if (index == 0) {
            vertices[initialIndex + index].setZPos(vertices[initialIndex + index].getPosition().z() * (coeffSec));
            vertices[initialIndex + index].setXPos(vertices[initialIndex + index].getPosition().x() * (coeffSec));
        } else {
            vertices[initialIndex + index].setZPos(vertices[initialIndex + index].getPosition().z() * (coeffSec));
            vertices[initialIndex - index].setZPos(vertices[initialIndex - index].getPosition().z() * (coeffSec));

            vertices[initialIndex + index].setXPos(vertices[initialIndex + index].getPosition().x() * (coeffSec));
            vertices[initialIndex - index].setXPos(vertices[initialIndex - index].getPosition().x() * (coeffSec));
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

        if (abs(vertices[i].getPosition().y() - yPos) > abs(vertices[lastIndex].getPosition().y() - yPos)) {

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

