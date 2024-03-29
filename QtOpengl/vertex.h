#ifndef VERTEX_H
#define VERTEX_H
#include <QVector2D>
#include <QVector3D>

class Vertex{
public:
    Vertex(const QVector3D& position){
        this->position = position;
        this->texCoord = QVector2D(0.0f, 0.0f);
        this->normal = position.normalized();
    }
    Vertex(const QVector3D& position, const QVector2D& texCoord){
        this->position = position;
        this->texCoord = texCoord;
        this->normal = position.normalized();
    }
    Vertex(const QVector3D& position, const QVector2D& texCoord, const QVector3D& normal){
        this->position = position;
        this->texCoord = texCoord;
        this->normal = normal;
    }

    QVector3D* GetPosition() { return &position; }
    QVector2D* GetTexCoord() { return &texCoord; }
    QVector3D* GetNormal() { return &normal; }

    static int positionOffset(){return offsetof(Vertex, position);}
    static int texCoordOffset(){return offsetof(Vertex, texCoord);}
    static int normalOffset(){return offsetof(Vertex, normal);}

private:
    QVector3D position;
    QVector2D texCoord;
    QVector3D normal;

};

#endif // VERTEX_H
