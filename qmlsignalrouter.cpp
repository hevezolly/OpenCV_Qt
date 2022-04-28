#include "CaptureHelper.h"

CaptureHelper::CaptureHelper(QCamera *camera, QObject *parent)
    : QObject{parent}
{
    m_capture = new QCameraImageCapture(camera);
    m_capture->setCaptureDestination(QCameraImageCapture::CaptureToBuffer);
    QObject::connect(&(*m_capture), &QCameraImageCapture::imageCaptured, &(*this), &CaptureHelper::handleImageCaptured);
}

void CaptureHelper::capture(){
    qInfo() << "on caputure" << Qt::flush;
    m_capture->capture();
}

void CaptureHelper::handleImageCaptured(int ,const QImage &preview){
    qInfo() << "emit" << Qt::flush;
    emit imageChanged(preview);
}
