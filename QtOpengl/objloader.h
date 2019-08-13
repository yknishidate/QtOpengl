#ifndef OBJ_LOADER_H_INCLUDED
#define OBJ_LOADER_H_INCLUDED

#include <string>
#include <QVector2D>
#include <QVector3D>


struct OBJIndex
{
    unsigned int vertexIndex;
    unsigned int uvIndex;
    unsigned int normalIndex;

    bool operator<(const OBJIndex& r) const { return vertexIndex < r.vertexIndex; }
};

class IndexedModel
{
public:
    std::vector<QVector3D> positions;
    std::vector<QVector2D> texCoords;
    std::vector<QVector3D> normals;
    std::vector<unsigned int> indices;

    void CalcNormals();
};

class OBJModel
{
public:
    std::vector<OBJIndex> OBJIndices;
    std::vector<QVector3D> vertices;
    std::vector<QVector2D> uvs;
    std::vector<QVector3D> normals;
    bool hasUVs;
    bool hasNormals;

    OBJModel(const std::string& fileName);

    IndexedModel ToIndexedModel();
private:
    unsigned int FindLastVertexIndex(const std::vector<OBJIndex*>& indexLookup, const OBJIndex* currentIndex, const IndexedModel& result);
    void CreateOBJFace(const std::string& line);

    QVector2D ParseOBJVec2(const std::string& line);
    QVector3D ParseOBJVec3(const std::string& line);
    OBJIndex ParseOBJIndex(const std::string& token, bool* hasUVs, bool* hasNormals);
};

#endif // OBJ_LOADER_H_INCLUDED
