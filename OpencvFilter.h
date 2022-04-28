#include <QAbstractVideoFilter>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#ifndef OPENCVFILTER_H
#define OPENCVFILTER_H


#endif // OPENCVFILTER_H

class OpencvFilter: public QAbstractVideoFilter{
    Q_OBJECT

   public:
       QVideoFilterRunnable *createFilterRunnable() override;

   private:
       friend class OpencvFilterRunnable;
};

class OpencvFilterRunnable : public QVideoFilterRunnable
{
public:
    OpencvFilterRunnable(OpencvFilter *filter)
    {
        Q_UNUSED(filter);
    }
    ~OpencvFilterRunnable() {}
    QVideoFrame run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags) override;
};
