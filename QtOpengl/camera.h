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

    QMatrix4x4 matrix;

private:
    QVector3D cameraPos;
    QVector3D targetPos;
};

#endif // CAMERA_H
