#ifndef VERTEX_H
#define VERTEX_H

#include <QVector3D>

class Vertex{
public:
    Vertex();
    Vertex(const QVector3D &position): position(position){}
    Vertex(const QVector3D &position, const QVector3D &color): position(position), color(color){}

    // 先頭から attribute へのバイト数
    static int positionOffset(){return offsetof(Vertex, position);}
    static int colorOffset(){return offsetof(Vertex, color);}
    // Vertex 1つ分のサイズ
    static int stride(){return sizeof(Vertex);}

private:
    QVector3D position;
    QVector3D color;
};

#endif // VERTEX_H
