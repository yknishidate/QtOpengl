#ifndef SHADER_H
#define SHADER_H
#include <QtOpenGL>


class Shader
{
public:
    Shader();
    void init();
    void update(QMatrix4x4 projMatrix, QMatrix4x4 viewMatrix);
    void update(QMatrix4x4 projMatrix, QMatrix4x4 viewMatrix, QMatrix4x4 modelMatrix, QMatrix3x3 normalMatrix);
    QOpenGLShaderProgram *program;

private:
    int projMatrixLoc;
    int mvMatrixLoc;
    int normalMatrixLoc;
    int lightPosLoc;
};

#endif // SHADER_H
