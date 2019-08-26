#ifndef CAMERA_H
#define CAMERA_H
#include <QtOpenGL>
#include <QVector3D>


class Camera
{
public:
    Camera(QVector3D cameraPos, QVector3D targetPos);
    void transform( int xRot, int yRot );
    void dolly( int degree );
    QMatrix4x4 getRotationMatrix(){return rotationMatrix;}
    //float getTheta(){return theta;}
    float getTheta();
    //float getPhi(){return phi;}
    float getPhi();
    float getLength(){return length;}

    QVector3D getCameraPos(){return cameraPos;}

    QMatrix4x4 matrix;

private:
    QVector3D cameraPos;
    QVector3D targetPos;
    QMatrix4x4 rotationMatrix;

    float theta;
    float phi;
    float length = 0;
};

#endif // CAMERA_H
