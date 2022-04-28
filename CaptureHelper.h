#ifndef CAPTUREHELPER_H
#define CAPTUREHELPER_H

#include <QCamera>
#include <QCameraImageCapture>
#include <QObject>

class CaptureHelper : public QObject
{
    Q_OBJECT
public:
    explicit CaptureHelper(QCamera *camera, QObject *parent = nullptr);
    ~CaptureHelper(){}

signals:
    void imageChanged(const QImage & image);

public slots:
    void capture();

private:
    void handleImageCaptured(int ,const QImage &preview);
    QCameraImageCapture *m_capture;

};

#endif // CAPTUREHELPER_H
