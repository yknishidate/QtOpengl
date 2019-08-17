#include "texture.h"

Texture::Texture(){

}

void Texture::init(QString fileName)
{
    // Load Texture
    texture = new QOpenGLTexture(QImage(fileName).mirrored());
    // Minification -> Nearest
    texture->setMinificationFilter(QOpenGLTexture::Nearest);
    // Magnification -> Linear
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    // Repeat
    texture->setWrapMode(QOpenGLTexture::Repeat);
}

void Texture::bind(){
    texture->bind();
}

void Texture::release(){
    texture->release();
}
