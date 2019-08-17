#include "objloader.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>

static bool CompareOBJIndexPtr(const OBJIndex* a, const OBJIndex* b);
static inline unsigned int FindNextChar(unsigned int start, const char* str, unsigned int length, char token);
static inline unsigned int ParseOBJIndexValue(const std::string& token, unsigned int start, unsigned int end);
static inline float ParseOBJFloatValue(const std::string& token, unsigned int start, unsigned int end);
static inline QVector<std::string> SplitString(const std::string &s, char delim);



OBJModel::OBJModel(const std::string& fileName)
{
    hasUVs = false;
    hasNormals = false;
    std::ifstream file;
    file.open(fileName.c_str());

    std::string line;
    if(file.is_open())
    {
        std::cout << "Seccess: Open file" << std::endl;
        while(file.good())
        {
            //1行取り出して"line"で受け取る
            getline(file, line);

            //1行の長さを"lineLength"に入れる
            unsigned int lineLength = line.length();

            //この行が1文字である=NULL文字のみの場合は飛ばす
            if(lineLength < 2)
                continue;

            //文字列をC言語の文字列表現にして"lineCStr"に入れる
            const char* lineCStr = line.c_str();

            //vertexかfaceかによって処理を分岐
            switch(lineCStr[0])
            {
                //vertex
                case 'v':
                    //texture coordinate
                    if(lineCStr[1] == 't')
                        this->uvs.push_back(ParseOBJVec2(line));
                    //normal
                    else if(lineCStr[1] == 'n')
                        this->normals.push_back(ParseOBJVec3(line));
                    //position
                    else if(lineCStr[1] == ' ' || lineCStr[1] == '\t')
                        this->vertices.push_back(ParseOBJVec3(line));
                break;
                //face
                case 'f':
                    CreateOBJFace(line);
                break;
                case 'o':
                    this->name = line.substr(2);
                break;
                //それ以外は無視
                default: break;
            };
        }
    }
    else
    {
        std::cerr << "Unable to load mesh: " << fileName << std::endl;
    }
}

void IndexedModel::CalcNormals()
{
    for(unsigned int i = 0; i < indices.size(); i += 3)
    {
        int i0 = indices[i];
        int i1 = indices[i + 1];
        int i2 = indices[i + 2];

        QVector3D v1 = positions[i1] - positions[i0];
        QVector3D v2 = positions[i2] - positions[i0];

        QVector3D normal = (QVector3D::crossProduct(v1, v2)).normalized();

        normals[i0] += normal;
        normals[i1] += normal;
        normals[i2] += normal;
    }

    for(unsigned int i = 0; i < positions.size(); i++)
        //normals[i] = (normals[i]).normalized();
        normals[i].normalize();
}

IndexedModel OBJModel::ToIndexedModel()
{
    IndexedModel result;
    IndexedModel normalModel;

    unsigned int numIndices = OBJIndices.size();

    QVector<OBJIndex*> indexLookup;

    for(unsigned int i = 0; i < numIndices; i++)
        indexLookup.push_back(&OBJIndices[i]);

    std::sort(indexLookup.begin(), indexLookup.end(), CompareOBJIndexPtr);

    std::map<OBJIndex, unsigned int> normalModelIndexMap;
    std::map<unsigned int, unsigned int> indexMap;

    for(unsigned int i = 0; i < numIndices; i++)
    {
        OBJIndex* currentIndex = &OBJIndices[i];

        QVector3D currentPosition = vertices[currentIndex->vertexIndex];
        QVector2D currentTexCoord;
        QVector3D currentNormal;

        if(hasUVs)
            currentTexCoord = uvs[currentIndex->uvIndex];
        else
            currentTexCoord = QVector2D(0,0);

        if(hasNormals)
            currentNormal = normals[currentIndex->normalIndex];
        else
            currentNormal = QVector3D(0,0,0);

        unsigned int normalModelIndex;
        unsigned int resultModelIndex;

        //Create model to properly generate normals on
        std::map<OBJIndex, unsigned int>::iterator it = normalModelIndexMap.find(*currentIndex);
        if(it == normalModelIndexMap.end())
        {
            normalModelIndex = normalModel.positions.size();

            normalModelIndexMap.insert(std::pair<OBJIndex, unsigned int>(*currentIndex, normalModelIndex));
            normalModel.positions.push_back(currentPosition);
            normalModel.texCoords.push_back(currentTexCoord);
            normalModel.normals.push_back(currentNormal);
        }
        else
            normalModelIndex = it->second;

        //Create model which properly separates texture coordinates
        unsigned int previousVertexLocation = FindLastVertexIndex(indexLookup, currentIndex, result);

        if(previousVertexLocation == (unsigned int)-1)
        {
            resultModelIndex = result.positions.size();

            result.positions.push_back(currentPosition);
            result.texCoords.push_back(currentTexCoord);
            result.normals.push_back(currentNormal);
        }
        else
            resultModelIndex = previousVertexLocation;

        normalModel.indices.push_back(normalModelIndex);
        result.indices.push_back(resultModelIndex);
        indexMap.insert(std::pair<unsigned int, unsigned int>(resultModelIndex, normalModelIndex));
    }

    if(!hasNormals)
    {
        normalModel.CalcNormals();

        for(unsigned int i = 0; i < result.positions.size(); i++)
            result.normals[i] = normalModel.normals[indexMap[i]];
    }
    result.name = name;

    return result;
};

unsigned int OBJModel::FindLastVertexIndex(const QVector<OBJIndex*>& indexLookup, const OBJIndex* currentIndex, const IndexedModel& result)
{
    unsigned int start = 0;
    unsigned int end = indexLookup.size();
    unsigned int current = (end - start) / 2 + start;
    unsigned int previous = start;

    while(current != previous)
    {
        OBJIndex* testIndex = indexLookup[current];

        if(testIndex->vertexIndex == currentIndex->vertexIndex)
        {
            unsigned int countStart = current;

            for(unsigned int i = 0; i < current; i++)
            {
                OBJIndex* possibleIndex = indexLookup[current - i];

                if(possibleIndex == currentIndex)
                    continue;

                if(possibleIndex->vertexIndex != currentIndex->vertexIndex)
                    break;

                countStart--;
            }

            for(unsigned int i = countStart; i < indexLookup.size() - countStart; i++)
            {
                OBJIndex* possibleIndex = indexLookup[current + i];

                if(possibleIndex == currentIndex)
                    continue;

                if(possibleIndex->vertexIndex != currentIndex->vertexIndex)
                    break;
                else if((!hasUVs || possibleIndex->uvIndex == currentIndex->uvIndex)
                    && (!hasNormals || possibleIndex->normalIndex == currentIndex->normalIndex))
                {
                    QVector3D currentPosition = vertices[currentIndex->vertexIndex];
                    QVector2D currentTexCoord;
                    QVector3D currentNormal;

                    if(hasUVs)
                        currentTexCoord = uvs[currentIndex->uvIndex];
                    else
                        currentTexCoord = QVector2D(0,0);

                    if(hasNormals)
                        currentNormal = normals[currentIndex->normalIndex];
                    else
                        currentNormal = QVector3D(0,0,0);

                    for(unsigned int j = 0; j < result.positions.size(); j++)
                    {
                        if(currentPosition == result.positions[j]
                            && ((!hasUVs || currentTexCoord == result.texCoords[j])
                            && (!hasNormals || currentNormal == result.normals[j])))
                        {
                            return j;
                        }
                    }
                }
            }

            return -1;
        }
        else
        {
            if(testIndex->vertexIndex < currentIndex->vertexIndex)
                start = current;
            else
                end = current;
        }

        previous = current;
        current = (end - start) / 2 + start;
    }

    return -1;
}

void OBJModel::CreateOBJFace(const std::string& line)
{
    QVector<std::string> tokens = SplitString(line, ' ');

    this->OBJIndices.push_back(ParseOBJIndex(tokens[1], &this->hasUVs, &this->hasNormals));
    this->OBJIndices.push_back(ParseOBJIndex(tokens[2], &this->hasUVs, &this->hasNormals));
    this->OBJIndices.push_back(ParseOBJIndex(tokens[3], &this->hasUVs, &this->hasNormals));

    if((int)tokens.size() > 4)
    {
        this->OBJIndices.push_back(ParseOBJIndex(tokens[1], &this->hasUVs, &this->hasNormals));
        this->OBJIndices.push_back(ParseOBJIndex(tokens[3], &this->hasUVs, &this->hasNormals));
        this->OBJIndices.push_back(ParseOBJIndex(tokens[4], &this->hasUVs, &this->hasNormals));
    }
}

OBJIndex OBJModel::ParseOBJIndex(const std::string& token, bool* hasUVs, bool* hasNormals)
{
    unsigned int tokenLength = token.length();
    const char* tokenString = token.c_str();

    unsigned int vertIndexStart = 0;
    unsigned int vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, '/');

    OBJIndex result;
    result.vertexIndex = ParseOBJIndexValue(token, vertIndexStart, vertIndexEnd);
    result.uvIndex = 0;
    result.normalIndex = 0;

    if(vertIndexEnd >= tokenLength)
        return result;

    vertIndexStart = vertIndexEnd + 1;
    vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, '/');

    result.uvIndex = ParseOBJIndexValue(token, vertIndexStart, vertIndexEnd);
    *hasUVs = true;

    if(vertIndexEnd >= tokenLength)
        return result;

    vertIndexStart = vertIndexEnd + 1;
    vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, '/');

    result.normalIndex = ParseOBJIndexValue(token, vertIndexStart, vertIndexEnd);
    *hasNormals = true;

    return result;
}

QVector3D OBJModel::ParseOBJVec3(const std::string& line)
{
    unsigned int tokenLength = line.length();
    const char* tokenString = line.c_str();

    unsigned int vertIndexStart = 2;

    while(vertIndexStart < tokenLength)
    {
        if(tokenString[vertIndexStart] != ' ')
            break;
        vertIndexStart++;
    }

    unsigned int vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');

    float x = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

    vertIndexStart = vertIndexEnd + 1;
    vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');

    float y = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

    vertIndexStart = vertIndexEnd + 1;
    vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');

    float z = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

    return QVector3D(x,y,z);

    //QVector3D(atof(tokens[1].c_str()), atof(tokens[2].c_str()), atof(tokens[3].c_str()))
}

QVector2D OBJModel::ParseOBJVec2(const std::string& line)
{
    unsigned int tokenLength = line.length();
    const char* tokenString = line.c_str();

    unsigned int vertIndexStart = 3;

    while(vertIndexStart < tokenLength)
    {
        if(tokenString[vertIndexStart] != ' ')
            break;
        vertIndexStart++;
    }

    unsigned int vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');

    float x = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

    vertIndexStart = vertIndexEnd + 1;
    vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');

    float y = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

    return QVector2D(x,y);
}

static bool CompareOBJIndexPtr(const OBJIndex* a, const OBJIndex* b)
{
    return a->vertexIndex < b->vertexIndex;
}

static inline unsigned int FindNextChar(unsigned int start, const char* str, unsigned int length, char token)
{
    unsigned int result = start;
    while(result < length)
    {
        result++;
        if(str[result] == token)
            break;
    }

    return result;
}

static inline unsigned int ParseOBJIndexValue(const std::string& token, unsigned int start, unsigned int end)
{
    return atoi(token.substr(start, end - start).c_str()) - 1;
}

static inline float ParseOBJFloatValue(const std::string& token, unsigned int start, unsigned int end)
{
    return atof(token.substr(start, end - start).c_str());
}

static inline QVector<std::string> SplitString(const std::string &s, char delim)
{
    QVector<std::string> elems;

    const char* cstr = s.c_str();
    unsigned int strLength = s.length();
    unsigned int start = 0;
    unsigned int end = 0;

    while(end <= strLength)
    {
        while(end <= strLength)
        {
            if(cstr[end] == delim)
                break;
            end++;
        }

        elems.push_back(s.substr(start, end - start));
        start = end + 1;
        end = start;
    }

    return elems;
}
