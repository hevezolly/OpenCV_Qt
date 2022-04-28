QT += quick
QT += multimedia multimediawidgets
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

android {
    OPENCVBUILD = D:/opencv/build_for_qt_android3
    INCLUDEPATH += $$OPENCVBUILD/install/sdk/native/jni/include

    OPENCV3RDPARTYLIBS = $$OPENCVBUILD/install/sdk/native/3rdparty/libs/armeabi-v7a
    OPENCVNATIVELIBS = $$OPENCVBUILD/install/sdk/native/libs/armeabi-v7a
    OPENCVSTATIC = $$OPENCVBUILD/install/sdk/native/staticlibs/armeabi-v7a


    LIBS += $$OPENCV3RDPARTYLIBS/liblibtiff.a

    LIBS += $$OPENCV3RDPARTYLIBS/liblibpng.a
    LIBS += $$OPENCV3RDPARTYLIBS/libittnotify.a

    LIBS += $$OPENCV3RDPARTYLIBS/libIlmImf.a
    LIBS += $$OPENCV3RDPARTYLIBS/libtegra_hal.a

    LIBS += $$OPENCV3RDPARTYLIBS/libcpufeatures.a

    LIBS += $$OPENCVSTATIC/libopencv_core.a \
    $$OPENCVSTATIC/libopencv_flann.a \
    $$OPENCVSTATIC/libopencv_imgproc.a \
    $$OPENCVSTATIC/libopencv_highgui.a \
    $$OPENCVSTATIC/libopencv_features2d.a \
    $$OPENCVSTATIC/libopencv_calib3d.a \
    $$OPENCVSTATIC/libopencv_ml.a \
    $$OPENCVSTATIC/libopencv_objdetect.a \
    $$OPENCVSTATIC/libopencv_photo.a \
    $$OPENCVSTATIC/libopencv_stitching.a \
    $$OPENCVSTATIC/libopencv_video.a \
    $$OPENCVNATIVELIBS/libopencv_java3.so \

    ANDROID_EXTRA_LIBS = $$OPENCVNATIVELIBS/libopencv_java3.so
    #ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android-sources
}
else{
    INCLUDEPATH += D:/opencv/build_for_qt_desctop3/install/include

    OPENCVBIN = D:/opencv/build_for_qt_desctop3/bin

    LIBS += $$OPENCVBIN/libopencv_core3415.dll \
    $$OPENCVBIN/libopencv_imgproc3415.dll \
    $$OPENCVBIN/libopencv_highgui3415.dll \
    $$OPENCVBIN/libopencv_imgcodecs3415.dll \
    $$OPENCVBIN/libopencv_features2d3415.dll \
    $$OPENCVBIN/libopencv_calib3d3415.dll \
}

SOURCES += \
        FrameToImage.cpp \
        capturedImageProcessor.cpp \
        filterRunnable.cpp \
        frameprocessor.cpp \
        main.cpp \
        qmlsignalrouter.cpp

RESOURCES += qml.qrc



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    CaptureHelper.h \
    ImConvert.h \
    OpencvFilter.h \
    capturedImageProcessor.h \
    frameprocessor.h

DISTFILES += \
    android-sources/AndroidManifest.xml
