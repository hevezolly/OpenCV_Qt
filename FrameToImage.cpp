#include "ImConvert.h"
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QQmlContext>
#include <opencv2/imgproc.hpp>

QImage ImConvert::QVideoFrameToQImage(QVideoFrame& videoFrame )
{
    if ( videoFrame.handleType() == QAbstractVideoBuffer::NoHandle )
    {
        videoFrame.map(QAbstractVideoBuffer::ReadOnly);
        QImage image = QImage(videoFrame.bits(),
                              videoFrame.width(),
                              videoFrame.height(),
                              videoFrame.bytesPerLine(),
                              QVideoFrame::imageFormatFromPixelFormat(videoFrame.pixelFormat()));
        videoFrame.unmap();
        if ( image.isNull() )
        {
            return QImage();
        }

        if ( image.format() != QImage::Format_ARGB32 )
        {
            image = image.convertToFormat( QImage::Format_ARGB32 );
        }

        return image;
    }

    if ( videoFrame.handleType() == QAbstractVideoBuffer::GLTextureHandle )
    {
        QImage image( videoFrame.width(), videoFrame.height(), QImage::Format_ARGB32 );
        GLuint textureId = static_cast<GLuint>( videoFrame.handle().toInt() );
        QOpenGLContext* ctx = QOpenGLContext::currentContext();
        QOpenGLFunctions* f = ctx->functions();
        GLuint fbo;
        f->glGenFramebuffers( 1, &fbo );
        GLint prevFbo;
        f->glGetIntegerv( GL_FRAMEBUFFER_BINDING, &prevFbo );
        f->glBindFramebuffer( GL_FRAMEBUFFER, fbo );
        f->glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId, 0 );
        f->glReadPixels( 0, 0,  videoFrame.width(),  videoFrame.height(), GL_RGBA, GL_UNSIGNED_BYTE, image.bits() );
        f->glBindFramebuffer( GL_FRAMEBUFFER, static_cast<GLuint>( prevFbo ) );
        return image.rgbSwapped();
    }

    return QImage();
}

cv::Mat ImConvert::imageToMat(QImage src)
{
    cv::Mat mat = cv::Mat(src.height(), src.width(), CV_8UC(src.depth()/8), (uchar*)src.bits(), src.bytesPerLine());
    cv::cvtColor(mat, mat, cv::COLOR_RGB2BGR);
    return mat;
}

QImage ImConvert::matToImage(cv::Mat mat)
{
    QImage b = QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
    return b.convertToFormat(QImage::Format_RGB32);
}
