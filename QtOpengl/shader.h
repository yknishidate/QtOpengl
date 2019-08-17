#ifndef SHADER_H
#define SHADER_H
#include <QtOpenGL>


class Shader
{
public:
    Shader();
    void init();
    void update(QMatrix4x4 proj, QMatrix4x4 camera);
    QOpenGLShaderProgram *program;

private:

    int projMatrixLoc;
    int mvMatrixLoc;
    int normalMatrixLoc;
    int lightPosLoc;
};

#endif // SHADER_H
