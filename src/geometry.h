#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QVector3D>

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

struct VertexData
{
    QVector3D position;
    QVector3D color;
};


class Geometry
{
public:
    Geometry();

private:
    std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
};

#endif // GEOMETRY_H
