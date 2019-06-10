#include <QtGui/QOpenGLShaderProgram>
#include "Skybox.h"

Skybox::Skybox() {
    // Faces list
    QOpenGLTexture::CubeMapFace cubeMapTarget[6] = {
            QOpenGLTexture::CubeMapNegativeX,
            QOpenGLTexture::CubeMapPositiveX,
            QOpenGLTexture::CubeMapNegativeY,
            QOpenGLTexture::CubeMapPositiveY,
            QOpenGLTexture::CubeMapNegativeZ,
            QOpenGLTexture::CubeMapPositiveZ
    };

    // Loads textures
    QImage skyboxImages[6];
    skyboxImages[0] = QImage(":/skybox/nx.png").convertToFormat(QImage::Format_RGBA8888);
    skyboxImages[1] = QImage(":/skybox/px.png").convertToFormat(QImage::Format_RGBA8888);
    skyboxImages[2] = QImage(":/skybox/ny.png").convertToFormat(QImage::Format_RGBA8888);
    skyboxImages[3] = QImage(":/skybox/py.png").convertToFormat(QImage::Format_RGBA8888);
    skyboxImages[4] = QImage(":/skybox/nz.png").convertToFormat(QImage::Format_RGBA8888);
    skyboxImages[5] = QImage(":/skybox/pz.png").convertToFormat(QImage::Format_RGBA8888);

    // Loads the skybox texture
    skyboxTexture = new QOpenGLTexture(QOpenGLTexture::TargetCubeMap);
    skyboxTexture->create();
    skyboxTexture->bind();
    skyboxTexture->setSize(skyboxImages[0].width(), skyboxImages[0].height(), skyboxImages[0].depth());
    skyboxTexture->setFormat(QOpenGLTexture::RGBAFormat);
    skyboxTexture->allocateStorage();
    skyboxTexture->setMinMagFilters(QOpenGLTexture::Nearest, QOpenGLTexture::Nearest);
    for (int i = 0; i < 6; i++) {
        uchar* bits = skyboxImages[i].bits();
        skyboxTexture->setData(0, 0, cubeMapTarget[i], QOpenGLTexture::RGBA, QOpenGLTexture::UInt8, bits, 0);
    }
    skyboxTexture->release();

    // Creates the the VBO (Vertex Buffer Object)
    skyboxVerticesBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    skyboxVerticesBuffer->create();
    auto *skyboxVertexDataArr = new float[skyboxVertices.size()];
    copy(skyboxVertices.begin(), skyboxVertices.end(), skyboxVertexDataArr);
    skyboxVerticesBuffer->bind();
    skyboxVerticesBuffer->allocate(skyboxVertexDataArr, skyboxVertices.size() * sizeof(float));
    skyboxVerticesBuffer->release();
    delete[] skyboxVertexDataArr;

}

void Skybox::bindTexture() {
    this->skyboxTexture->bind(0);
}

void Skybox::releaseTexture() {
    this->skyboxTexture->release(0);
}

void Skybox::bindVBO() {
    this->skyboxVerticesBuffer->bind();
}

void Skybox::releaseVBO() {
    this->skyboxVerticesBuffer->release();
}
