#include <OpencvFilter.h>
#include <QCamera>
#include <QCameraImageCapture>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickItem>
#include <QQuickView>
#include <capturedImageProcessor.h>
#include <CaptureHelper.h>


int main(int argc, char *argv[])
{
    QGuiApplication app(argc,argv);
    qmlRegisterType<OpencvFilter>("com.opencv.filter", 1, 0, "OpencvFilter");
    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    QObject::connect(view.engine(), &QQmlEngine::quit,
                     qApp, &QGuiApplication::quit);

    capturedImageProcessor *processor = new capturedImageProcessor();

    QQmlEngine *engine = view.engine();
        engine->addImageProvider(QLatin1String("capturedimage"), processor);

    view.setSource(QUrl("qrc:///main.qml"));

#ifndef _WIN32
    view.showFullScreen();
#else
    view.resize(1280, 720);
#endif
    view.show();

    QQuickItem *viewRoot = view.rootObject();
    QCamera *camera = qvariant_cast<QCamera*>(viewRoot->findChild<QObject*>("camera")->property("mediaObject"));


    CaptureHelper *camera_helper = new CaptureHelper(camera);

    QObject::connect(&(*viewRoot), SIGNAL(processButtonPressed()), &(*camera_helper), SLOT(capture()));

    QObject *im = viewRoot->findChild<QQuickItem*>("photoPreview");

    qInfo() << viewRoot << Qt::flush;
    qInfo() << im << Qt::flush;
    QObject::connect(&(*camera_helper), &CaptureHelper::imageChanged, [=](const QImage & qimage){
        qInfo() << qimage << Qt::flush;
        processor->setBaseImage(qimage);
        im->setProperty("source", "image://capturedimage/preview");
        im->setProperty("visible", true);
    });




    return app.exec();
}
