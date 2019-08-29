#include "camera.h"

Camera::Camera( QVector3D cameraPos, QVector3D targetPos)
{
    this->cameraPos = cameraPos;
    this->targetPos = targetPos;
    this->length = (targetPos - cameraPos).length();
}

void Camera::transform( int xRot, int yRot){
    QMatrix4x4 rotation;
    rotation.setToIdentity();
    rotation.rotate(xRot / 16.0f, 1, 0, 0);
    rotation.rotate(yRot / 16.0f, 0, 1, 0);

    cameraPos = QVector3D(0, 0, length) * rotation;

    matrix.setToIdentity();
    matrix.lookAt(cameraPos, targetPos, QVector3D(0, 1, 0));
}

void Camera::dolly( int degree ){
    length -= degree/10;
}

