#include "OpencvFilter.h"
#include "ImConvert.h"
#include "qdebug.h"
#include "frameprocessor.h"


QVideoFrame OpencvFilterRunnable::run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags){
    Q_UNUSED(surfaceFormat);
    Q_UNUSED(flags);
    QImage img = ImConvert::QVideoFrameToQImage(*input);
    if (img.isNull()){
        return *input;
    }
    cv::Mat mat = ImConvert::imageToMat(img);

    cv::Mat resultMat = processImage(mat);

    QImage resultIm = ImConvert::matToImage(resultMat);
    QVideoFrame resultFrame = QVideoFrame(resultIm);
    return resultFrame;
}

QVideoFilterRunnable *OpencvFilter::createFilterRunnable()
{
    return new OpencvFilterRunnable(this);
}

