#include "mesh.h"
#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QOpenGLExtraFunctions>


Mesh::Mesh()
    : ibo(QOpenGLBuffer::IndexBuffer){
}

Mesh::Mesh(const QString& fileName)
    : ibo(QOpenGLBuffer::IndexBuffer){
    init(OBJModel(fileName.toStdString()).ToIndexedModel());
}

// Primitives
Mesh::Mesh(const int type)
    : ibo(QOpenGLBuffer::IndexBuffer){
    IndexedModel indexModel;
    float size = 5.0f;
    float radius = 5.0f;
    int stacks = 32;
    int slices = 64;

    switch(type){
    case CUBE:
        indexModel.name = "Cube";

        // position
        indexModel.positions.push_back(QVector3D(-1.0f, -1.0f, -1.0f)*size);
        indexModel.positions.push_back(QVector3D(-1.0f, -1.0f,  1.0f)*size);
        indexModel.positions.push_back(QVector3D(-1.0f,  1.0f,  1.0f)*size);
        indexModel.positions.push_back(QVector3D(-1.0f, -1.0f, -1.0f)*size);
        indexModel.positions.push_back(QVector3D(-1.0f,  1.0f,  1.0f)*size);
        indexModel.positions.push_back(QVector3D(-1.0f,  1.0f, -1.0f)*size);

        indexModel.positions.push_back(QVector3D( 1.0f, -1.0f, -1.0f)*size);
        indexModel.positions.push_back(QVector3D(-1.0f, -1.0f, -1.0f)*size);
        indexModel.positions.push_back(QVector3D(-1.0f,  1.0f, -1.0f)*size);
        indexModel.positions.push_back(QVector3D( 1.0f, -1.0f, -1.0f)*size);
        indexModel.positions.push_back(QVector3D(-1.0f,  1.0f, -1.0f)*size);
        indexModel.positions.push_back(QVector3D( 1.0f,  1.0f, -1.0f)*size);

        indexModel.positions.push_back(QVector3D(-1.0f, -1.0f, -1.0f)*size);
        indexModel.positions.push_back(QVector3D( 1.0f, -1.0f, -1.0f)*size);
        indexModel.positions.push_back(QVector3D( 1.0f, -1.0f,  1.0f)*size);
        indexModel.positions.push_back(QVector3D(-1.0f, -1.0f, -1.0f)*size);
        indexModel.positions.push_back(QVector3D( 1.0f, -1.0f,  1.0f)*size);
        indexModel.positions.push_back(QVector3D(-1.0f, -1.0f,  1.0f)*size);

        indexModel.positions.push_back(QVector3D( 1.0f, -1.0f,  1.0f)*size);
        indexModel.positions.push_back(QVector3D( 1.0f, -1.0f, -1.0f)*size);
        indexModel.positions.push_back(QVector3D( 1.0f,  1.0f, -1.0f)*size);
        indexModel.positions.push_back(QVector3D( 1.0f, -1.0f,  1.0f)*size);
        indexModel.positions.push_back(QVector3D( 1.0f,  1.0f, -1.0f)*size);
        indexModel.positions.push_back(QVector3D( 1.0f,  1.0f,  1.0f)*size);

        indexModel.positions.push_back(QVector3D(-1.0f,  1.0f, -1.0f)*size);
        indexModel.positions.push_back(QVector3D(-1.0f,  1.0f,  1.0f)*size);
        indexModel.positions.push_back(QVector3D( 1.0f,  1.0f,  1.0f)*size);
        indexModel.positions.push_back(QVector3D(-1.0f,  1.0f, -1.0f)*size);
        indexModel.positions.push_back(QVector3D( 1.0f,  1.0f,  1.0f)*size);
        indexModel.positions.push_back(QVector3D( 1.0f,  1.0f, -1.0f)*size);

        indexModel.positions.push_back(QVector3D(-1.0f, -1.0f,  1.0f)*size);
        indexModel.positions.push_back(QVector3D( 1.0f, -1.0f,  1.0f)*size);
        indexModel.positions.push_back(QVector3D( 1.0f,  1.0f,  1.0f)*size);
        indexModel.positions.push_back(QVector3D(-1.0f, -1.0f,  1.0f)*size);
        indexModel.positions.push_back(QVector3D( 1.0f,  1.0f,  1.0f)*size);
        indexModel.positions.push_back(QVector3D(-1.0f,  1.0f,  1.0f)*size);

        // Tex Coord
        indexModel.texCoords.push_back(QVector2D(0.0f, 0.0f));
        indexModel.texCoords.push_back(QVector2D(0.33f, 0.0f));
        indexModel.texCoords.push_back(QVector2D(0.0f, 0.5f));
        indexModel.texCoords.push_back(QVector2D(0.33f, 0.5f));

        indexModel.texCoords.push_back(QVector2D(0.0f, 0.5f));
        indexModel.texCoords.push_back(QVector2D(0.33f, 0.5f));
        indexModel.texCoords.push_back(QVector2D(0.0f, 1.0f));
        indexModel.texCoords.push_back(QVector2D(0.33f, 1.0f));

        indexModel.texCoords.push_back(QVector2D(0.66f, 0.5f));
        indexModel.texCoords.push_back(QVector2D(1.0f, 0.5f));
        indexModel.texCoords.push_back(QVector2D(0.66f, 1.0f));
        indexModel.texCoords.push_back(QVector2D(1.0f, 1.0f));

        indexModel.texCoords.push_back(QVector2D(0.66f, 0.0f));
        indexModel.texCoords.push_back(QVector2D(1.0f, 0.0f));
        indexModel.texCoords.push_back(QVector2D(0.66f, 0.5f));
        indexModel.texCoords.push_back(QVector2D(1.0f, 0.5f));

        indexModel.texCoords.push_back(QVector2D(0.33f, 0.0f));
        indexModel.texCoords.push_back(QVector2D(0.66f, 0.0f));
        indexModel.texCoords.push_back(QVector2D(0.33f, 0.5f));
        indexModel.texCoords.push_back(QVector2D(0.66f, 0.5f));

        indexModel.texCoords.push_back(QVector2D(0.33f, 0.5f));
        indexModel.texCoords.push_back(QVector2D(0.66f, 0.5f));
        indexModel.texCoords.push_back(QVector2D(0.33f, 1.0f));
        indexModel.texCoords.push_back(QVector2D(0.66f, 1.0f));

        indexModel.texCoords.push_back(QVector2D(0.66f, 0.0f));
        indexModel.texCoords.push_back(QVector2D(1.0f, 0.0f));
        indexModel.texCoords.push_back(QVector2D(0.66f, 0.5f));
        indexModel.texCoords.push_back(QVector2D(1.0f, 0.5f));

        indexModel.texCoords.push_back(QVector2D(0.33f, 0.0f));
        indexModel.texCoords.push_back(QVector2D(0.66f, 0.0f));
        indexModel.texCoords.push_back(QVector2D(0.33f, 0.5f));
        indexModel.texCoords.push_back(QVector2D(0.66f, 0.5f));

        indexModel.texCoords.push_back(QVector2D(0.33f, 0.5f));
        indexModel.texCoords.push_back(QVector2D(0.66f, 0.5f));
        indexModel.texCoords.push_back(QVector2D(0.33f, 1.0f));
        indexModel.texCoords.push_back(QVector2D(0.66f, 1.0f));

        // Normal
        indexModel.normals.push_back(QVector3D(-1.0f, 0.0f, 0.0f));
        indexModel.normals.push_back(QVector3D(-1.0f, 0.0f, 0.0f));
        indexModel.normals.push_back(QVector3D(-1.0f, 0.0f, 0.0f));
        indexModel.normals.push_back(QVector3D(-1.0f, 0.0f, 0.0f));
        indexModel.normals.push_back(QVector3D(-1.0f, 0.0f, 0.0f));
        indexModel.normals.push_back(QVector3D(-1.0f, 0.0f, 0.0f));

        indexModel.normals.push_back(QVector3D(0.0f, 0.0f, -1.0f));
        indexModel.normals.push_back(QVector3D(0.0f, 0.0f, -1.0f));
        indexModel.normals.push_back(QVector3D(0.0f, 0.0f, -1.0f));
        indexModel.normals.push_back(QVector3D(0.0f, 0.0f, -1.0f));
        indexModel.normals.push_back(QVector3D(0.0f, 0.0f, -1.0f));
        indexModel.normals.push_back(QVector3D(0.0f, 0.0f, -1.0f));

        indexModel.normals.push_back(QVector3D(0.0f, -1.0f, 0.0f));
        indexModel.normals.push_back(QVector3D(0.0f, -1.0f, 0.0f));
        indexModel.normals.push_back(QVector3D(0.0f, -1.0f, 0.0f));
        indexModel.normals.push_back(QVector3D(0.0f, -1.0f, 0.0f));
        indexModel.normals.push_back(QVector3D(0.0f, -1.0f, 0.0f));
        indexModel.normals.push_back(QVector3D(0.0f, -1.0f, 0.0f));

        indexModel.normals.push_back(QVector3D( 1.0f, 0.0f, 0.0f));
        indexModel.normals.push_back(QVector3D( 1.0f, 0.0f, 0.0f));
        indexModel.normals.push_back(QVector3D( 1.0f, 0.0f, 0.0f));
        indexModel.normals.push_back(QVector3D( 1.0f, 0.0f, 0.0f));
        indexModel.normals.push_back(QVector3D( 1.0f, 0.0f, 0.0f));
        indexModel.normals.push_back(QVector3D( 1.0f, 0.0f, 0.0f));

        indexModel.normals.push_back(QVector3D( 0.0f, 1.0f, 0.0f));
        indexModel.normals.push_back(QVector3D( 0.0f, 1.0f, 0.0f));
        indexModel.normals.push_back(QVector3D( 0.0f, 1.0f, 0.0f));
        indexModel.normals.push_back(QVector3D( 0.0f, 1.0f, 0.0f));
        indexModel.normals.push_back(QVector3D( 0.0f, 1.0f, 0.0f));
        indexModel.normals.push_back(QVector3D( 0.0f, 1.0f, 0.0f));

        indexModel.normals.push_back(QVector3D( 0.0f, 0.0f, 1.0f));
        indexModel.normals.push_back(QVector3D( 0.0f, 0.0f, 1.0f));
        indexModel.normals.push_back(QVector3D( 0.0f, 0.0f, 1.0f));
        indexModel.normals.push_back(QVector3D( 0.0f, 0.0f, 1.0f));
        indexModel.normals.push_back(QVector3D( 0.0f, 0.0f, 1.0f));
        indexModel.normals.push_back(QVector3D( 0.0f, 0.0f, 1.0f));

        indexModel.indices = {
            0,  1,  2,  3,  4,  5, // 左
            6,  7,  8,  9, 10, 11, // 裏
           12, 13, 14, 15, 16, 17, // 下
           18, 19, 20, 21, 22, 23, // 右
           24, 25, 26, 27, 28, 29, // 上
           30, 31, 32, 33, 34, 35  // 前
        };

        break;

    case SPHERE:
        indexModel.name = "Sphere";
        // Position, TexCoord, Normal
        for (int j = 0; j <= stacks; ++j){
            const float t(static_cast<float>(j) / static_cast<float>(stacks));
            const float y(cos(M_PI * t) * radius), r(sin(M_PI * t) * radius);
            for (int i = 0; i <= slices; ++i){
                const float s(static_cast<float>(i) / static_cast<float>(slices));
                const float z(r * cos(M_PI * 2 * s)), x(r * sin(M_PI * 2 * s));
                indexModel.positions.push_back(QVector3D(x, y, z));
                indexModel.texCoords.push_back(QVector2D(1.0f/slices * i, 1.0f-(1.0f/stacks * j)));
                indexModel.normals.push_back(QVector3D(x, y, z).normalized());
            }
        }
        // Index
        for (int j = 0; j < stacks; ++j){
            const int k((slices + 1) * j);
            for (int i = 0; i < slices; ++i){
                // 頂点のインデックス
                const GLuint k0(k + i);
                const GLuint k1(k0 + 1);
                const GLuint k2(k1 + slices);
                const GLuint k3(k2 + 1);
                // 左下の三角形
                indexModel.indices.push_back(k0);
                indexModel.indices.push_back(k2);
                indexModel.indices.push_back(k3);
                // 右上の三角形
                indexModel.indices.push_back(k0);
                indexModel.indices.push_back(k3);
                indexModel.indices.push_back(k1);
            }
        }
        break;

    case PLANE: // Plane
        indexModel.name = "Plane";

        // position
        indexModel.positions.push_back(QVector3D(-1.0f, 0.0f,  1.0f)*size*5);
        indexModel.positions.push_back(QVector3D( 1.0f, 0.0f,  1.0f)*size*5);
        indexModel.positions.push_back(QVector3D( 1.0f, 0.0f, -1.0f)*size*5);
        indexModel.positions.push_back(QVector3D(-1.0f, 0.0f, -1.0f)*size*5);

        // Tex Coord
        indexModel.texCoords.push_back(QVector2D(1.0f, 0.0f));
        indexModel.texCoords.push_back(QVector2D(1.0f, 1.0f));
        indexModel.texCoords.push_back(QVector2D(0.0f, 1.0f));
        indexModel.texCoords.push_back(QVector2D(1.0f, 0.0f));

        // Normal
        indexModel.normals.push_back(QVector3D(0.0f, 1.0f, 0.0f));
        indexModel.normals.push_back(QVector3D(0.0f, 1.0f, 0.0f));
        indexModel.normals.push_back(QVector3D(0.0f, 1.0f, 0.0f));
        indexModel.normals.push_back(QVector3D(0.0f, 1.0f, 0.0f));

        indexModel.indices = { 0,  1,  2,  0,  2,  3 };
        break;
    }

    init(indexModel);
}



Mesh::~Mesh(){
    vbo.destroy();
    ibo.destroy();
    qDebug() << "Mesh Deleted";
}

void Mesh::createSphere(float radius, int stacks, int slices){
    indexModel.name = "Sphere";
    // Position, TexCoord, Normal
    for (int j = 0; j <= stacks; ++j){
        const float t(static_cast<float>(j) / static_cast<float>(stacks));
        const float y(cos(M_PI * t) * radius), r(sin(M_PI * t) * radius);
        for (int i = 0; i <= slices; ++i){
            const float s(static_cast<float>(i) / static_cast<float>(slices));
            const float z(r * cos(M_PI * 2 * s)), x(r * sin(M_PI * 2 * s));
            indexModel.positions.push_back(QVector3D(x, y, z));
            indexModel.texCoords.push_back(QVector2D(1.0f/slices * i, 1.0f-(1.0f/stacks * j)));
            indexModel.normals.push_back(QVector3D(x, y, z).normalized());
        }
    }
    // Index
    for (int j = 0; j < stacks; ++j){
        const int k((slices + 1) * j);
        for (int i = 0; i < slices; ++i){
            // 頂点のインデックス
            const GLuint k0(k + i);
            const GLuint k1(k0 + 1);
            const GLuint k2(k1 + slices);
            const GLuint k3(k2 + 1);
            // 左下の三角形
            indexModel.indices.push_back(k0);
            indexModel.indices.push_back(k2);
            indexModel.indices.push_back(k3);
            // 右上の三角形
            indexModel.indices.push_back(k0);
            indexModel.indices.push_back(k3);
            indexModel.indices.push_back(k1);
        }
    }
    init(indexModel);
}

void Mesh::changeSphere(float radius, int stacks, int slices){
    // Position, TexCoord, Normal
    indexModel.positions.clear();
    indexModel.texCoords.clear();
    indexModel.normals.clear();
    indexModel.indices.clear();

    for (int j = 0; j <= stacks; ++j){
        const float t(static_cast<float>(j) / static_cast<float>(stacks));
        const float y(cos(M_PI * t) * radius), r(sin(M_PI * t) * radius);
        for (int i = 0; i <= slices; ++i){
            const float s(static_cast<float>(i) / static_cast<float>(slices));
            const float z(r * cos(M_PI * 2 * s)), x(r * sin(M_PI * 2 * s));
            indexModel.positions.push_back(QVector3D(x, y, z));
            indexModel.texCoords.push_back(QVector2D(1.0f/slices * i, 1.0f-(1.0f/stacks * j)));
            indexModel.normals.push_back(QVector3D(x, y, z).normalized());
        }
    }
    // Index
    for (int j = 0; j < stacks; ++j){
        const int k((slices + 1) * j);
        for (int i = 0; i < slices; ++i){
            // 頂点のインデックス
            const GLuint k0(k + i);
            const GLuint k1(k0 + 1);
            const GLuint k2(k1 + slices);
            const GLuint k3(k2 + 1);
            // 左下の三角形
            indexModel.indices.push_back(k0);
            indexModel.indices.push_back(k2);
            indexModel.indices.push_back(k3);
            // 右上の三角形
            indexModel.indices.push_back(k0);
            indexModel.indices.push_back(k3);
            indexModel.indices.push_back(k1);
        }
    }
    change(indexModel);
}

void Mesh::init(const IndexedModel& model){
    qDebug() << "---initMesh()---";
    initializeOpenGLFunctions();

    texCoordOffset = model.positions.size()*sizeof(model.positions[0]);
    normalOffset   = texCoordOffset + model.texCoords.size()*sizeof(model.texCoords[0]);
    vboTotalSize   = normalOffset   + model.normals.size()*sizeof(model.normals[0]);

    vbo.create();
    vbo.bind();
    vbo.allocate( &model.positions[0], vboTotalSize);    // "&qvec[0]" で渡す
    vbo.write( texCoordOffset, &model.texCoords[0],
               model.texCoords.size()*sizeof(model.texCoords[0]));
    vbo.write( normalOffset, &model.normals[0],
               model.normals.size()*sizeof(model.normals[0]));
//    vbo.release();

    ibo.create();
    ibo.bind();
    ibo.allocate(&model.indices[0], model.indices.size() *sizeof(model.indices[0]));
    m_numIndices = model.indices.size();

    name = model.name;

    initCubeMap();

    qDebug() << "Name          :" << QString::fromStdString(model.name);
    qDebug() << "Points        :" << model.positions.size();
    qDebug() << "Indeces       :" << model.indices.size();
    qDebug() << "vboTotalSize  :" << vboTotalSize;
    qDebug() << "vbo ID        :" << vbo.bufferId();
    qDebug() << "ibo ID        :" << ibo.bufferId();
}

void Mesh::change(const IndexedModel &model){
    qDebug() << "---Change Mesh---";
    vbo.destroy();
    ibo.destroy();

    texCoordOffset = model.positions.size()*sizeof(model.positions[0]);
    normalOffset   = texCoordOffset + model.texCoords.size()*sizeof(model.texCoords[0]);
    vboTotalSize   = normalOffset   + model.normals.size()*sizeof(model.normals[0]);

    vbo.create();
    vbo.bind();
    vbo.allocate( &model.positions[0], vboTotalSize);    // "&qvec[0]" で渡す
    vbo.write( texCoordOffset, &model.texCoords[0],
               model.texCoords.size()*sizeof(model.texCoords[0]));
    vbo.write( normalOffset, &model.normals[0],
               model.normals.size()*sizeof(model.normals[0]));

    ibo.create();
    ibo.bind();
    ibo.allocate(&model.indices[0], model.indices.size() *sizeof(model.indices[0]));
    m_numIndices = model.indices.size();

    qDebug() << "Points        :" << model.positions.size();
    qDebug() << "Indeces       :" << model.indices.size();
}



void Mesh::draw(QOpenGLShaderProgram *shader_program, GLenum displayMode, QOpenGLTexture *texture, int materialType){
    if(displayMode == GL_LINE_STRIP){
        glLineWidth(0.8f);
        shader_program->setUniformValue("textureSample", 0);
        shader_program->setUniformValue("wire", 1);
    }else{
        shader_program->setUniformValue("wire", 0);
        shader_program->setUniformValue("materialType", materialType);
        switch (materialType) {
        case 0: // Diffuse
            if( texture != nullptr){
                texture->bind();
                shader_program->setUniformValue("textureSample", 1);
            }else{
                shader_program->setUniformValue("textureSample", 0);
            }
            break;
        case 1: // Metal
            glBindTexture(GL_TEXTURE_CUBE_MAP, textureGL);
            shader_program->setUniformValue("textureSample", 1);
            break;
        case 2: // Glass
            break;
        case 3: // Light
            break;
        }
    }

    //shader_program->bind();
    vao.bind();
    ibo.bind();
    vbo.bind();

    shader_program->setAttributeBuffer(0, GL_FLOAT, 0, 3);  //stride = 0(default)
    shader_program->enableAttributeArray(0);
    shader_program->setAttributeBuffer(1, GL_FLOAT, texCoordOffset, 2);
    shader_program->enableAttributeArray(1);
    shader_program->setAttributeBuffer(2, GL_FLOAT, normalOffset, 3);
    shader_program->enableAttributeArray(2);

    glDrawElements(displayMode, m_numIndices, GL_UNSIGNED_INT, 0);   //mode count type indices
    //vbo.release();
    //ibo.release();
    //vao.release();
    //shader_program->release();
    if(displayMode == GL_TRIANGLES && texture != nullptr){
        texture->release();
    }
}

void Mesh::initCubeMap(){
    QImage x = QImage(":/resource/cube_PX.png").rgbSwapped();
    QImage y = QImage(":/resource/cube_PY.png").rgbSwapped();
    QImage z = QImage(":/resource/cube_PZ.png").rgbSwapped();
    QImage _x = QImage(":/resource/cube_NX.png").rgbSwapped();
    QImage _y = QImage(":/resource/cube_NY.png").rgbSwapped();
    QImage _z = QImage(":/resource/cube_NZ.png").rgbSwapped();
    glGenTextures(1, &textureGL);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureGL);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*) x.bits());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*) y.bits());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*) z.bits());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*) _x.bits());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*) _y.bits());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*) _z.bits());
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glBindTexture(GL_TEXTURE_CUBE_MAP, textureGL);
//    shader_program->setUniformValue("textureSample", 1);
}
