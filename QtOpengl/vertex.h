#ifndef VERTEX_H
#define VERTEX_H

#include <QVector3D>

class Vertex{
public:
    // コンストラクタ
    Vertex();
    Vertex(const QVector3D &position): m_position(position){}

    // Vertex classの先頭から m_position へのバイト数を返す
    static int positionOffset(){return offsetof(Vertex, m_position);}
    // Vertex 1つ分のサイズを返す
    static int stride(){return sizeof(Vertex);}

private:
    QVector3D m_position;
};

#endif // VERTEX_H
