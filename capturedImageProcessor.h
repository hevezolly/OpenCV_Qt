#ifndef CAPTUREDIMAGEPROCESSOR_H
#define CAPTUREDIMAGEPROCESSOR_H

#include <QObject>
#include <QQuickImageProvider>

class capturedImageProcessor : public QQuickImageProvider
{
public:
    explicit capturedImageProcessor();

    void setBaseImage(const QImage image);

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;
private:
    QImage m_image;
};

#endif // CAPTUREDIMAGEPROCESSOR_H
