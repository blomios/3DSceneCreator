/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "geometryengine.h"

#include <QVector2D>
#include <QVector3D>
#include <math.h>

#define PI 3.14159265


GeometryEngine::GeometryEngine()
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    figure.nbStages = 100;
    figure.nbVerticesPerStage = 100;

    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // Creates VBO and EBO for the skybox
    skyboxVerticesBuffer.create();
    skyboxIndicesBuffer.create();

    // Initializes cube geometry and transfers it to VBOs
    initGeometry();

    // Initializes the skybox
    //initializeSkybox();
}

GeometryEngine::GeometryEngine(FigureData data)
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    figure = data;

    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // Creates VBO and EBO for the skybox
    skyboxVerticesBuffer.create();
    skyboxIndicesBuffer.create();

    // Initializes cube geometry and transfers it to VBOs
    initGeometry();
}

GeometryEngine::~GeometryEngine()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}

//Place the original point positions
void GeometryEngine::placePointsOriginalPosition(){

    float P = figure.cylinderSize * 100 / (1+figure.cylinderSize);

    int N = P * figure.nbStages / 100;

    //set nb indices and vertices to 0
    nbrIndices = 0;
    nbrVertices = 0;

    //Set position of each vertices
    for(int i = 0; i <= (figure.nbStages - N) / 2; i++){

        for(int j = 0; j < figure.nbVerticesPerStage; j++){

            float x = cos( ((2*PI) / figure.nbVerticesPerStage) * j ) * sin( (PI / (figure.nbStages)) * i );
            float z = sin( ((2*PI) / figure.nbVerticesPerStage) * j ) * sin( (PI / (figure.nbStages)) * i ) ;

            QVector3D color = QVector3D(1.0f, abs(x),0.0f); //Set a color with a nice gradient color :p

            //Add the created vertice in the tab
            VertexData vertex = {QVector3D(
                                 x, //X position
                                 cos((PI / (figure.nbStages)) * i), //Y position
                                 z), //Z position
                                 color};

            vertices.push_back( vertex);

            //Increase vertices nbr
            nbrVertices++;
        }
    }

    //Set position of each vertices
    for(int i = (figure.nbStages - N) / 2 + 1; i <= (figure.nbStages - N) / 2 + N; i++){

        for(int j = 0; j < figure.nbVerticesPerStage; j++){

            float x = cos( ((2*PI) / figure.nbVerticesPerStage) * j ) * sin( (PI / (figure.nbStages)) * ((figure.nbStages - N) / 2) );
            float z = sin( ((2*PI) / figure.nbVerticesPerStage) * j ) * sin( (PI / (figure.nbStages)) * ((figure.nbStages - N) / 2) ) ;

            QVector3D color = QVector3D(1.0f, abs(x),0.0f); //Set a color with a nice gradient color :p

            //Add the created vertice in the tab
            VertexData vertex = {QVector3D(
                                 x, //X position
                                 cos((PI / (figure.nbStages)) * ((figure.nbStages - N) / 2)), //Y position
                                 z), //Z position
                                 color};

            vertices.push_back( vertex);

            //Increase vertices nbr
            nbrVertices++;
        }
    }

    //Set position of each vertices
    for(int i = (figure.nbStages - N) / 2 + N + 1; i <= figure.nbStages; i++){

        for(int j = 0; j < figure.nbVerticesPerStage; j++){

            float x = cos( ((2*PI) / figure.nbVerticesPerStage) * j ) * sin( (PI / (figure.nbStages)) * i );
            float z = sin( ((2*PI) / figure.nbVerticesPerStage) * j ) * sin( (PI / (figure.nbStages)) * i ) ;

            QVector3D color = QVector3D(1.0f, abs(x),0.0f); //Set a color with a nice gradient color :p
            QVector2D texCoords = QVector2D((float)j/(figure.nbVerticesPerStage - 1), (float)i/(figure.nbStages)); // TODO Test purpose

            //Add the created vertice in the tab
            VertexData vertex = {QVector3D(
                                 x, //X position
                                 cos((PI / (figure.nbStages)) * i), //Y position
                                 z), //Z position
                    color, texCoords};

            vertices.push_back( vertex);

            //Increase vertices nbr
            nbrVertices++;
        }
    }


    //Set indices tab (link the vertices of stage N withe the vertices of stage N+1 to create faces) don't touch it is working... I think
    for(int i = 1; i <= figure.nbStages; i++){
        for(int j = 0; j < figure.nbVerticesPerStage; j++){

            std::vector<GLushort> arr = {
            };

            arr.push_back(figure.nbVerticesPerStage * i + j);
            arr.push_back(figure.nbVerticesPerStage * (i-1) + j);
            arr.push_back(figure.nbVerticesPerStage * (i) + ((j + 1) % figure.nbVerticesPerStage));

            arr.push_back(figure.nbVerticesPerStage * (i-1) + j);
            arr.push_back(figure.nbVerticesPerStage * (i-1) + ((j + 1) % figure.nbVerticesPerStage));
            arr.push_back(figure.nbVerticesPerStage * (i) + ((j + 1) % figure.nbVerticesPerStage));

            for(int j = 0 ; j < arr.size(); j++){
                indices.push_back(arr[j]);

                nbrIndices++;
            }

        }
    }

    setBuffers();
}

//Set the buffers, don't touch it's working too
void GeometryEngine::setBuffers(){

    //Set vertex buffer
    VertexData *arr = new VertexData[vertices.size()];
    copy(vertices.begin(),vertices.end(),arr);
    arrayBuf.bind();
    arrayBuf.allocate(arr, nbrVertices * sizeof(VertexData));
    arrayBuf.release();
    delete[] arr;

    //Set indeces buffer
    GLushort *arrIndices = new GLushort[indices.size()];
    copy(indices.begin(),indices.end(),arrIndices);
    indexBuf.bind();
    indexBuf.allocate(arrIndices, nbrIndices * sizeof(GLushort));
    indexBuf.release();
     delete[] arrIndices;

}

//Remove a bottleneck
void GeometryEngine::removeBottleNeck(int bnIndex, bool deleteBnFromTheList){

    float yPos = bottleNecks[bnIndex].yPos;
    float xSize = bottleNecks[bnIndex].xSize;
    float ySize = bottleNecks[bnIndex].ySize;

    int initialIndex = getStagesFromYPosition(yPos);

    int index = 0;

    float coeff = 1/xSize;

    while(initialIndex+index < vertices.size() && initialIndex - index >=0 && abs(vertices[initialIndex + index].position.y() - yPos) < ySize){

        float coeffSec = coeff *  cos((PI/2/ySize) * abs(vertices[initialIndex + index].position.y() - yPos));

        if(coeffSec >= 1){
            vertices[initialIndex + index].position.setZ( vertices[initialIndex + index].position.z() * (coeffSec ) );
            vertices[initialIndex - index].position.setZ( vertices[initialIndex - index].position.z() * (coeffSec ) );

            vertices[initialIndex + index].position.setX( vertices[initialIndex + index].position.x() * (coeffSec ) );
            vertices[initialIndex - index].position.setX( vertices[initialIndex - index].position.x() * (coeffSec ) );
        }



        index++;

    }

    arrayBuf.destroy();
    indexBuf.destroy();

    arrayBuf.create();
    indexBuf.create();

    setBuffers();

    if(deleteBnFromTheList)
        bottleNecks.erase(bottleNecks.begin()+bnIndex);

}

void GeometryEngine::updateBottleNeck(int bnIndex, float yPos, float xSize, float ySize){

    removeBottleNeck(bnIndex, false);

    setBottleNeck(yPos, xSize, ySize);

    bottleNecks[bnIndex] = { yPos,  xSize,  ySize};


}

void GeometryEngine::addBottleNeck(float yPos, float xSize, float ySize){

    BottleNeck bn = {yPos, xSize, ySize};

    bottleNecks.push_back(bn);

    setBottleNeck(yPos, xSize, ySize);

}

void GeometryEngine::setBottleNeck(float yPos, float xSize, float ySize){

    int initialIndex = getStagesFromYPosition(yPos);

    int index = 0;

    float coeff = 1/xSize;

    while(initialIndex+index < vertices.size() && initialIndex - index >=0 && abs(vertices[initialIndex + index].position.y() - yPos) < ySize){

        float coeffSec = coeff *  cos((PI/2/ySize) * abs(vertices[initialIndex + index].position.y() - yPos));

        if(coeffSec >= 1){
            vertices[initialIndex + index].position.setZ( vertices[initialIndex + index].position.z() / (coeffSec ) );
            vertices[initialIndex - index].position.setZ( vertices[initialIndex - index].position.z() / (coeffSec ) );

            vertices[initialIndex + index].position.setX( vertices[initialIndex + index].position.x() / (coeffSec ) );
            vertices[initialIndex - index].position.setX( vertices[initialIndex - index].position.x() / (coeffSec ) );
        }



        index++;

    }

    arrayBuf.destroy();
    indexBuf.destroy();

    arrayBuf.create();
    indexBuf.create();

    setBuffers();

}

//Get the closest stage from the y pos entered
int GeometryEngine::getStagesFromYPosition(float yPos){

    int lastIndex = 0;

    for(int i = figure.nbVerticesPerStage; i < nbrVertices; i+= figure.nbVerticesPerStage){

        if(abs(vertices[i].position.y() - yPos) > abs(vertices[lastIndex].position.y() - yPos)){
            return lastIndex;
        }

        else {
            lastIndex = i;
        }

    }

}

//Initialize the geometry
void GeometryEngine::initGeometry() {
    placePointsOriginalPosition();
}

//Draw the geometry
void GeometryEngine::drawGeometry(QOpenGLShaderProgram *program) {
    placePointsOriginalPosition();
    // Tell OpenGL which VBOs to use


    arrayBuf.bind();
    indexBuf.bind();


    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int colorLocation = program->attributeLocation("color");
    program->enableAttributeArray(colorLocation);
    program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinates
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int textureLocation = program->attributeLocation("texCoord");
    program->enableAttributeArray(textureLocation);
    program->setAttributeBuffer(textureLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1

    glDrawElements(GL_TRIANGLES, nbrIndices, GL_UNSIGNED_SHORT, 0);
    arrayBuf.release();
    indexBuf.release();

}

void GeometryEngine::setNbOfStages(int nbOfStages) {
    vertices.clear();
    indices.clear();
    arrayBuf.destroy();
    indexBuf.destroy();

    figure.nbStages = nbOfStages;

    arrayBuf.create();
    indexBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    initGeometry();

    for(int i = 0; i < bottleNecks.size(); i++){

        setBottleNeck(bottleNecks[i].yPos, bottleNecks[i].xSize, bottleNecks[i].ySize);

    }
}

void GeometryEngine::setNbOfVerticesPerStage(int nbOfVerticesPerStage) {
    vertices.clear();
    indices.clear();
    arrayBuf.destroy();
    indexBuf.destroy();

    figure.nbVerticesPerStage = nbOfVerticesPerStage;

    arrayBuf.create();
    indexBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    initGeometry();

    for(int i = 0; i < bottleNecks.size(); i++){

        setBottleNeck(bottleNecks[i].yPos, bottleNecks[i].xSize, bottleNecks[i].ySize);

    }
}

void GeometryEngine::initializeSkybox() {
    // Faces list
    GLenum cubeMapTarget[6] = {
            GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB,
            GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB,
            GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB,
            GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB,
            GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB,
            GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB
    };

    // Loads textures
    QImage* skyboxImages[6];
    skyboxImages[0] = new QImage(":/nx.png");
    skyboxImages[1] = new QImage(":/px.png");
    skyboxImages[2] = new QImage(":/ny.png");
    skyboxImages[3] = new QImage(":/py.png");
    skyboxImages[4] = new QImage(":/nz.png");
    skyboxImages[5] = new QImage(":/pz.png");

    // Generates the ID for the texture
    glGenTextures(1, &skyboxTextureId);

    for (int i = 0; i < 6; i++) {
        int width = skyboxImages[i]->width();
        int height = skyboxImages[i]->height();
        uchar* bits = skyboxImages[i]->bits();
        glTexImage2D(cubeMapTarget[i], 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bits);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP);
}

void GeometryEngine::drawSkybox(QOpenGLShaderProgram *program) {
    // Cube size
    float t = 1.0;

    // Negative X face
    SkyboxVertexData vertexData = {QVector3D(-t, -t, -t), QVector3D(1.0, 1.0, 1.0), QVector3D(-t, -t, -t)};
    skyboxVertices.push_back(vertexData);
    SkyboxVertexData vertexData2 = {QVector3D(-t, t, -t), QVector3D(1.0, 1.0, 1.0), QVector3D(-t, t, -t)};
    skyboxVertices.push_back(vertexData2);
    SkyboxVertexData vertexData3 = {QVector3D(-t, -t, t), QVector3D(1.0, 1.0, 1.0), QVector3D(-t, -t, t)};
    skyboxVertices.push_back(vertexData3);
    SkyboxVertexData vertexData4 = {QVector3D(-t, t, t), QVector3D(1.0, 1.0, 1.0), QVector3D(-t, t, t)};
    skyboxVertices.push_back(vertexData4);

    // Positive Z Face
    SkyboxVertexData vertexData5 = {QVector3D(-t, -t, t), QVector3D(1.0, 1.0, 1.0), QVector3D(-t, -t, t)};
    skyboxVertices.push_back(vertexData5);
    SkyboxVertexData vertexData6 = {QVector3D(-t, t, t), QVector3D(1.0, 1.0, 1.0), QVector3D(-t, t, t)};
    skyboxVertices.push_back(vertexData6);
    SkyboxVertexData vertexData7 = {QVector3D(t, -t, t), QVector3D(1.0, 1.0, 1.0), QVector3D(t, -t, t)};
    skyboxVertices.push_back(vertexData7);
    SkyboxVertexData vertexData8 = {QVector3D(t, t, t), QVector3D(1.0, 1.0, 1.0), QVector3D(t, t, t)};
    skyboxVertices.push_back(vertexData8);

    // Negative Z face
    SkyboxVertexData vertexData9 = {QVector3D(-t, -t, -t), QVector3D(1.0, 1.0, 1.0), QVector3D(-t, -t, -t)};
    skyboxVertices.push_back(vertexData9);
    SkyboxVertexData vertexData10 = {QVector3D(t, -t, -t), QVector3D(1.0, 1.0, 1.0), QVector3D(t, -t, -t)};
    skyboxVertices.push_back(vertexData10);
    SkyboxVertexData vertexData11 = {QVector3D(-t, t, -t), QVector3D(1.0, 1.0, 1.0), QVector3D(-t, t, -t)};
    skyboxVertices.push_back(vertexData11);
    SkyboxVertexData vertexData12 = {QVector3D(t, t, -t), QVector3D(1.0, 1.0, 1.0), QVector3D(t, t, -t)};
    skyboxVertices.push_back(vertexData12);


    skyboxIndices = {
            0, 1, 2, 1, 2, 3, // Negative X face
            4, 5, 6, 5, 6, 7, // Positive X face
            8, 9, 10, 9, 10, 11, // Negative Y face
            12, 13, 14, 13, 14, 15, // Positive Y face
            16, 17, 18, 17, 18, 19, // Negative Z face
            20, 21, 22, 21, 22, 23 // Positive Z face
    };

    // VBO (Vertex Buffer Object)
    //skyboxVerticesBuffer(QOpenGLBuffer::VertexBuffer);
    auto *skyboxVertexDataArr = new SkyboxVertexData[skyboxVertices.size()];
    copy(skyboxVertices.begin(), skyboxVertices.end(), skyboxVertexDataArr);
    skyboxVerticesBuffer.bind();
    skyboxVerticesBuffer.allocate(skyboxVertexDataArr, skyboxVertices.size() * sizeof(SkyboxVertexData));
    skyboxVerticesBuffer.release();
    delete[] skyboxVertexDataArr;


    // EBO (Element Buffer Object)
    //QOpenGLBuffer skyboxIndicesBuffer(QOpenGLBuffer::IndexBuffer);
    auto *skyboxIndicesArr = new GLushort[skyboxIndices.size()];
    copy(skyboxIndices.begin(), skyboxIndices.end(), skyboxIndicesArr);
    skyboxIndicesBuffer.bind();
    skyboxIndicesBuffer.allocate(skyboxIndicesArr, skyboxIndices.size() * sizeof(GLushort));
    skyboxIndicesBuffer.release();
    delete[] skyboxIndicesArr;

    // Offset for position
    quintptr offset = 0;

    skyboxVerticesBuffer.bind();
    skyboxIndicesBuffer.bind();

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(SkyboxVertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int colorLocation = program->attributeLocation("color");
    program->enableAttributeArray(colorLocation);
    program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(SkyboxVertexData));

    // Offset for texture coordinates
    //offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int textureLocation = program->attributeLocation("texCoord");
    program->enableAttributeArray(textureLocation);
    program->setAttributeBuffer(textureLocation, GL_FLOAT, offset, 3, sizeof(SkyboxVertexData));

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);

    skyboxVerticesBuffer.release();
    skyboxIndicesBuffer.release();
}