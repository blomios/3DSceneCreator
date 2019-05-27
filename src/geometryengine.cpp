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

GeometryEngine::GeometryEngine()
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    initGeometry();
}

GeometryEngine::~GeometryEngine()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}

//Refresh geometry when form proprieties is changed
void GeometryEngine::refreshGeometry() {

    //Set manualy form proprieties (it will be deleted when the interface will be created)
    figure.nbStages = this->nbOfStages;
    figure.nbVerticesPerStage = this->nbOfVerticesPerStage;

    //Init vertices and indices number to 0
    nbrIndices = 0;
    nbrVertices = 0;

    //Create vertices tab with the differents form proprieties
    for(int i = 0; i <= figure.nbStages; i++){
        for(int j = 0; j < figure.nbVerticesPerStage; j++){

            float x = cos( ((2*PI) / figure.nbVerticesPerStage) * j ) * sin( (PI / (figure.nbStages)) * i );
            float z = sin( ((2*PI) / figure.nbVerticesPerStage) * j ) * sin( (PI / (figure.nbStages)) * i ) ;
            QVector3D color = QVector3D(1.0f, abs(x),0.0f);
             //qDebug() << color;

            vertices.push_back( {QVector3D(
                                 x, //X position
                                 (2.5f / (figure.nbStages+1)) * i - 2.5f/2, //Y position
                                 z), //Z position
                                 color} ); //color
            nbrVertices++;
        }
    }


    //create indices tab withe the differents form proprieties
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

    //delete arr;
    arr = new VertexData[vertices.size()];
    copy(vertices.begin(),vertices.end(),arr);
    arrayBuf.bind();
    arrayBuf.allocate(arr, nbrVertices * sizeof(VertexData));

    //delete arrIndices;
    arrIndices = new GLushort[indices.size()];
    copy(indices.begin(),indices.end(),arrIndices);
    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(arrIndices, nbrIndices * sizeof(GLushort));

}

void GeometryEngine::initGeometry() {
    refreshGeometry();
}

void GeometryEngine::drawGeometry(QOpenGLShaderProgram *program) {
    refreshGeometry();

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

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLES, nbrIndices, GL_UNSIGNED_SHORT, 0);
}

void GeometryEngine::setNbOfStages(int nbOfStages) {
    this->nbOfStages = nbOfStages;
}

void GeometryEngine::setNbOfVerticesPerStage(int nbOfVerticesPerStage) {
    this->nbOfVerticesPerStage = nbOfVerticesPerStage;
}
