#ifndef INC_3DSCENECREATOR_MODELVERTEX_H
#define INC_3DSCENECREATOR_MODELVERTEX_H


#include <QtGui/QVector3D>
#include <QtGui/QVector2D>

class ModelVertex {
private:
    QVector3D position;
    QVector3D color;
    QVector2D textureCoords;
    QVector3D normals;
public:
    ModelVertex();

    ModelVertex(QVector3D position, QVector3D color, QVector2D textCoords, QVector3D normalCoord);

    const QVector3D getPosition() const;

    void setPosition(const QVector3D &position);

    void setXPos(float x);

    void setYPos(float y);

    void setZPos(float z);

    const QVector3D &getColor() const;

    void setColor(const QVector3D &color);

    const QVector2D &getTextureCoords() const;

    void setTextureCoords(const QVector2D &textureCoords);
};


#endif //INC_3DSCENECREATOR_MODELVERTEX_H
