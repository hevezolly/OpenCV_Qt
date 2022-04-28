#include <QCameraImageCapture>
#include <qobject.h>


class ImageCaptureHelper: public QObject{
    Q_OBJECT
public:
    ImageCaptureHelper(QCameraImageCapture* capture, QObject *parent = 0) : QObject(parent) {
        m_capture = capture;
    }
    virtual ~ImageCaptureHelper() {}

    void clicked()  {
         m_capture->capture();
    }
private:
    QCameraImageCapture *m_capture;
};
