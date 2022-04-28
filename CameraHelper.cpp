#include <QCamera>
#include <QCameraImageCapture>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

class CameraHelper: public QObject{
    Q_OBJECT

public:
    CameraHelper(QCamera *camera, QObject *parent = nullptr):
        QObject{parent}
    {
        m_capture = new QCameraImageCapture(camera, this);
        m_capture->setCaptureDestination(QCameraImageCapture::CaptureToBuffer);
        connect(m_capture, &QCameraImageCapture::imageCaptured, this, &CameraHelper::handleImageCaptured);
    }

    ~CameraHelper(){}


signals:
    void imageChanged(const QImage & image);



public slots:
    void capture(){
        if(m_capture)
            m_capture->capture();
    }

private:
    void handleImageCaptured(int , const QImage &preview){
        emit imageChanged(preview);
    }
    QCameraImageCapture *m_capture = nullptr;
};
