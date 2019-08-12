#ifndef VERTEX_H
#define VERTEX_H

#include <QVector3D>

class Vertex{
public:
    Vertex();
    Vertex(const QVector3D &position): m_position(position){}

    // 先頭から position へのバイト数
    static int positionOffset(){return offsetof(Vertex, m_position);}
    // Vertex 1つ分のサイズ
    static int stride(){return sizeof(Vertex);}

private:
    QVector3D m_position;
};

#endif // VERTEX_H
