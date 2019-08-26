#include "camera.h"

Camera::Camera( QVector3D cameraPos, QVector3D targetPos)
{
    this->cameraPos = cameraPos;
    this->targetPos = targetPos;
    this->rotationMatrix.setToIdentity();
    this->theta = 0.0f;
    this->phi = 0.0f;
}

void Camera::transform( int xRot, int yRot){
    //QMatrix4x4 rotation;
    //rotation.setToIdentity();
    //rotation.rotate(xRot / 16.0f, 1, 0, 0);
    //rotation.rotate(yRot / 16.0f, 0, 1, 0);

    rotationMatrix.setToIdentity();
    rotationMatrix.rotate(xRot / 16.0f, 1, 0, 0);
    rotationMatrix.rotate(yRot / 16.0f, 0, 1, 0);
    theta = xRot/16.0f;
    phi   = yRot/16.0f;
    //qDebug() << "CameraRotation" << "(" << theta << "," << phi << ")";


    // Camera Dolly
    matrix.setToIdentity();
    //matrix.lookAt(cameraPos * rotation, targetPos, QVector3D(0, 1, 0));
    matrix.lookAt(cameraPos * rotationMatrix, targetPos, QVector3D(0, 1, 0));
}

void Camera::dolly( int degree ){
    QVector3D relativeVec = targetPos - cameraPos;
    QVector3D cameraDir = relativeVec.normalized();
    if(relativeVec.length() > 2 || degree < 0){
        cameraPos = cameraPos + cameraDir * degree/10;
    }
    length = relativeVec.length();
}

float Camera::getTheta()
{
    return qAcos(cameraPos.z() / cameraPos.length());
}

float Camera::getPhi()
{
    return qAtan(cameraPos.y() / cameraPos.x());
}
