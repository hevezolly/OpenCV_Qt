#ifndef IMCONVERT_H
#define IMCONVERT_H
#include <QVideoFrame>
#include <opencv2/core/core.hpp>

namespace ImConvert{
    QImage QVideoFrameToQImage(QVideoFrame& videoFrame );
    cv::Mat imageToMat(QImage src);
    QImage matToImage(cv::Mat mat);
}
#endif // IMCONVERT_H
