#include "camera.h"

Camera::Camera( QVector3D cameraPos, QVector3D targetPos)
{
    this->cameraPos = cameraPos;
    this->targetPos = targetPos;
}

void Camera::transform( int xRot, int yRot){
    QMatrix4x4 rotation;
    rotation.setToIdentity();
    rotation.rotate(xRot / 16.0f, 1, 0, 0);
    rotation.rotate(yRot / 16.0f, 0, 1, 0);

    // Camera Dolly
    matrix.setToIdentity();
    matrix.lookAt(cameraPos * rotation, targetPos, QVector3D(0, 1, 0));
}

void Camera::dolly( int degree ){
    QVector3D relativeVec = targetPos - cameraPos;
    QVector3D cameraDir = relativeVec.normalized();
    if(relativeVec.length() > 2 || degree < 0){
        cameraPos = cameraPos + cameraDir * degree/10;
    }
}
