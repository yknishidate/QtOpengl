#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <QtOpenGL>
#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <string>

struct OBJIndex{
    unsigned int vertexIndex;
    unsigned int uvIndex;
    unsigned int normalIndex;

    bool operator<(const OBJIndex& r) const { return vertexIndex < r.vertexIndex; }
};


class IndexedModel{
public:
    QVector<QVector3D> positions;
    QVector<QVector2D> texCoords;
    QVector<QVector3D> normals;
    QVector<GLuint> indices;
    std::string name;

    void CalcNormals();
};

class OBJModel{
public:
    QVector<OBJIndex> OBJIndices;
    QVector<QVector3D> vertices;
    QVector<QVector2D> uvs;
    QVector<QVector3D> normals;
    bool hasUVs;
    bool hasNormals;
    std::string name;

    OBJModel(const std::string& fileName);

    IndexedModel ToIndexedModel();
private:
    unsigned int FindLastVertexIndex(const QVector<OBJIndex*>& indexLookup, const OBJIndex* currentIndex, const IndexedModel& result);
    void CreateOBJFace(const std::string& line);

    QVector2D ParseOBJVec2(const std::string& line);
    QVector3D ParseOBJVec3(const std::string& line);
    OBJIndex ParseOBJIndex(const std::string& token, bool* hasUVs, bool* hasNormals);
};


#endif // OBJLOADER_H
