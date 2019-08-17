#include "shader.h"

Shader::Shader()
{
}

void Shader::init(){
    program = new QOpenGLShaderProgram();
    program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl");
    program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl");
    program->link();
    program->bind();

    // Get Location from Shader
    projMatrixLoc = program->uniformLocation("projMatrix");
    mvMatrixLoc = program->uniformLocation("mvMatrix");
    program->setUniformValue("texture", 0);
    //normalMatrixLoc = shader_program->uniformLocation("normalMatrix");
    //lightPosLoc = shader_program->uniformLocation("lightPos");

    // Light
    //shader_program->setUniformValue(lightPosLoc, QVector3D(0, 0, 70));
}


void Shader::update(QMatrix4x4 proj, QMatrix4x4 camera){
    program->bind();
    program->setUniformValue(projMatrixLoc, proj);
    program->setUniformValue(mvMatrixLoc, camera);
}
