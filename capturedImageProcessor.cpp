#include <capturedImageProcessor.h>
#include "qdebug.h"
#include "ImConvert.h"
#include <frameprocessor.h>

capturedImageProcessor::capturedImageProcessor()
    : QQuickImageProvider(QQuickImageProvider::Image)
{
    m_image = QImage();
}

void capturedImageProcessor::setBaseImage(const QImage surce){
    cv::Mat mat = ImConvert::imageToMat(surce);
    cv::Mat result =  processImage(mat);
    m_image = ImConvert::matToImage(result);
}

QImage capturedImageProcessor::requestImage(const QString&,QSize* size, const QSize&){
    qInfo() << "requested width: " << size->width() << Qt::flush;
    qInfo() << "requested height: " << size->height() << Qt::flush;
    qInfo() << "actual width: " << m_image.width() << Qt::flush;
    qInfo() << "actual height: " << m_image.height() << Qt::flush;
    return m_image;
}
