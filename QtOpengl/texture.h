#ifndef TEXTURE_H
#define TEXTURE_H
#include <QtOpenGL>
#include <QString>


class Texture
{
public:
    Texture();
    void init(QString fileName);
    void bind();
    void release();
    QOpenGLTexture *texture;
};

#endif // TEXTURE_H
