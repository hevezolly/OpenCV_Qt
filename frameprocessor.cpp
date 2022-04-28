#include "frameprocessor.h"
#include "opencv2/imgproc.hpp"

cv::Mat processImage(const cv::Mat mat)
{
    cv::Mat result;
    cv::bitwise_not(mat, result);
    return result;
}
