
# Подключение OpenCV к Qt для разработки кроссплатформенных приложений.

Ниже будет подробно представлен способ подключения библиотеки OpenCV к Qt для разработки desktop и android приложений на windows.
Из-за большой разницы между платформами, библиотеку придется подключать отдельно для мобильной и десктопной версии.

## Предварительные действия и установки.

Я использовал Qt версии 5.15.2 и OpenCV 3.4.15. Кроме этого, в обоих случаях понадобится CMake. Я использовал CMakeGui 3.23.0.

1)	Qt можно скачать с официального сайта https://www.qt.io/download

    После открытия скаченного файла «qt-unified-windows-x86-4.3.0-1-online.exe» необходимо авторизоваться (или зарегистрироваться) в свой Qt аккаунт.

    Далее – выбор директории для установки. В моем случае – это D:\Qt

    Во время выбора компонентов для установки убедитесь, что вы выбрали Qt 5.15.2 и в качестве дополнительных компонентов - 
    MinGW 64-bit (в моем случае – MinGW 8.1.0 64-bit)

    Завершите установку.

    Дополнительные компоненты можно добавить отдельно с помощью установленного вместе с Qt приложения Qt Maintenance Tool.

2)	OpenCV необходимой версии тоже можно скачать с официального сайта https://opencv.org/releases/. Убедитесь, что выбираете 
    OpenCV-3.4.15, т.к. для других версий процесс подключения может отличаться. 

    Скачайте архив Sources и разархивируйте в вашу файловую систему. В моем случае – в D:\opencv.

3)	Необходимую версию CMake можно найти здесь: https://cmake.org/download/
    скачайте установщик на windows и следуйте инструкции.

    Кроме всего прочего, необходимо добавить в переменную среды PATH
    следующий путь:
    {директория установки qt}\Tools\{mingw той версии, которую вы выбрали при установке qt}\bin

    В моем случае это
    D:\Qt\Tools\mingw810_64\bin

    В вашем случае она может отличаться.
    После этого необходимо перезагрузить компьютер, чтобы изменения вступили в силу.


## Подключение OpenCV для десктоп приложений


Прежде всего необходимо собрать установленную библиотеку opencv с помощью mingw. Для Этого используем CMake.

1)  Для начала создайте пустую папку, в которой будет сохранена сборка.
    В моем случае – это 
    D:\opencv\build_for_qt_desctop3

2)	Запустите CMake

3)	В поле «Where is the source code» укажите 
    D:\opencv\opencv-3.4.15

    В поле «Where to build the binaries» укажите только что созданную папку
    D:/opencv/build_for_qt_desctop3

    ![image](https://user-images.githubusercontent.com/28929816/165719671-92610f79-052e-438a-a5a2-c487d9023cd8.png)


4)	Нажмите **Configure**


5)	В качестве генератора выберите «MinGW Makefiles»
    Выберите пункт выберите пункт «Specify native compilers»
    ![image](https://user-images.githubusercontent.com/28929816/165720261-04206d63-1302-408f-8420-13385c143e76.png)

 
    Нажмите **Next**



6)	В качестве компилятора C укажите 
    `D:/Qt/Tools/mingw810_64/bin/gcc.exe`

    В качестве компилятора С++ укажите
    `D:/Qt/Tools/mingw810_64/bin/g++.exe`

    (В вашем случае путь может отличаться. Провельте, что путь к mingw и его версия совпадает с тем, что вы добавили в PATH в предыдущей части)
    ![image](https://user-images.githubusercontent.com/28929816/165720552-78c928c9-d321-4f1b-bfcf-71088fa78e60.png)

    Нажмите **Finish**, подождите пока пройдет конфигурация

7)	В CMake отметьте следующие пункты:

    **WITH_QT** 

    **WITH_OPENGL**

    Укажите в **Qt5_DIR** `D:/Qt/5.15.2/mingw81_64/lib/cmake/Qt5`
    
    (Для этого может понадобиться нажать Add Entry)
    (Ваш путь может отличаться. Обратите внимание на версию mingw)
    

    Уберите отметку с пункта **ENABLE_PRECOMPILED_HEADERS**


8)	Нажмите **Configure** снова, подождите пока конфигурация закончится

9)	Добавьте или установите следующие параметры:

    **QT_MAKE_EXECUTABLE**:
    `D:/Qt/5.15.2/mingw81_64/bin/qmake.exe` 

    **Qt5Concurrent_DIR**:
    `D:/Qt/5.15.2/mingw81_64/lib/cmake/Qt5Concurrent`

    **Qt5Core_DIR**:
    `D:/Qt/5.15.2/mingw81_64/lib/cmake/Qt5Core`

    **Qt5Gui_DIR**: 
    `D:/Qt/5.15.2/mingw81_64/lib/cmake/Qt5Gui`

    **Qt5Test_DIR**:
    `D:/Qt/5.15.2/mingw81_64/lib/cmake/Qt5Test`

    **Qt5Widgets_DIR**:
    `D:/Qt/5.15.2/mingw81_64/lib/cmake/Qt5Widgets`

    **Qt5OpenGL_DIR**:
    `D:/Qt/5.15.2/mingw81_64/lib/cmake/Qt5OpenGL`

    **CMAKE_BUILD_TYPE**:
    `Release`
 
    **OPENCV_VS_VERSIONINFO_SKIP**:
    `1`
	 
10)	Нажмите **Configure** а после – **Generate**

11)	Откройте командную строку в папке со сборкой 
    `D:\opencv\build_for_qt_desctop3`

    выполните следующие команды:
    ```
    mingw32-make -j 8
    
    mingw32-make install
    ```

Добавьте в переменную среды *PATH* следующий путь:

`D:\opencv\build_for_qt_desctop3\install\x64\mingw\bin`

Перезагрузите компьютер.

#### На этом сборка библиотеки завершена. 


Для использования этой библиотеки в проекте Qt необходимо добавить в файл 
{имя проекта}.pro следующие строки :
```
INCLUDEPATH += D:\opencv\build_for_qt_desctop3\install\include

OPENCVBIN = D:\opencv\build_for_qt_desctop3\bin

LIBS += $$OPENCVBIN\libopencv_core3415.dll \
$$OPENCVBIN\libopencv_imgproc3415.dll \
$$OPENCVBIN\libopencv_highgui3415.dll \
$$OPENCVBIN\libopencv_imgcodecs3415.dll \
$$OPENCVBIN\libopencv_features2d3415.dll \
$$OPENCVBIN\libopencv_calib3d3415.dll \
```

## Подключение OpenCV для android приложений

Для сборки opencv под андроид дополнительно понадобится установить 
Apache-ant-1.10.12. Это можно сделать отсюда https://ant.apache.org/bindownload.cgi

Распакуйте скаченный архив в файловую систему, я распаковал в 

`D:\Components`

Кроме того необходимы будут инструменты jdk, sdk и ndk.
Jdk необходим 11 версии (более новые не поддерживаются qt 5.15) его можно скачать отсюда 	https://adoptium.net/temurin/archive

Откройте Qt-Creator перейдите в 

Инструменты -> Параметры -> Устройства
(Tools -> Options -> Devices)

Укажите путь к распакованной папке в Размещение JDK
![image](https://user-images.githubusercontent.com/28929816/165724190-9b80a5ba-dd0f-42ca-9871-a92b41796e2c.png)
 
 
Qt Creator может настроить sdk и ndk самостоятельно, для этого введите
в поле «Размещение SDK для Android» путь установки и нажмите
**Настроить SDK**.

![image](https://user-images.githubusercontent.com/28929816/165724241-3c38b3f0-11ef-4441-9cc3-20b4e4ef9190.png)

 
Вместе с SDK будут добавлены и несколько комплектов ndk
 
Я использую версию 22.1, выберите ее и нажмите **Make Default**

![image](https://user-images.githubusercontent.com/28929816/165724289-236a61ee-18ad-49bb-a560-8602a451816e.png)

Если у вас отсутствует ndk этой версии, ее можно установить в SDK Manager ниже, под вкладкой инструменты.
  

### Сборка:

1)	Для начала создайте пустую папку, в которой будет сохранена сборка.
    В моем случае – это 
    `D:\opencv\build_for_qt_android3`

2)	Запустите CMake

3)	В поле «Where is the source code» укажите 
    `D:/opencv/opencv-3.4.15`

    В поле «Where to build the binaries» укажите только что созданную папку
    `D:/opencv/build_for_qt_android3`
    
    ![image](https://user-images.githubusercontent.com/28929816/165724651-e43c1dba-ae13-44eb-b517-5c69d258db2e.png)


4)	Нажмите **Configure**

5)	В качестве генератора укажите «MinGW Makefiles»
    Выберите пункт «Specify toolchain file for cross-compiling»

    ![image](https://user-images.githubusercontent.com/28929816/165724681-162c0748-e7d4-47f5-a8c2-187846705787.png)

    Нажмите **Next**

6)	В поле «Specify the Toolchain file» выберите следующий путь:

    `D:/Components/SDKForQt/ndk/22.1.7171670/build/cmake/android.toolchain.cmake`

    Где `D:/Components/SDKForQt` – путь до sdk, созданного Qt-Creator
    а `22.1.7171670` – версия ndk, который был помечен «Default» 
    в Qt-Creator

 
7)	Нажмите **Finish**

    Подождите пока пройдет процесс конфигурации, 

    игнорируйте сообщение об ошибке.


8)	Добавьте в CMake следующие параметры: 

    **ANDROID_NDK**: `D:/Components/SDKForQt/ndk/22.1.7171670`

    **ANDROID_SDK_ROOT**:  `D:/Components/SDKForQt`

    **ANT_EXECUTABLE**:  `D:/Components/apache-ant-1.10.12/bin/ant.bat`
        Где apache-ant-1.10.12 – папка из распакованного архива ant.

    **ANDROID_STL**:  `c++_shared`

    **ANDROID_ABI**:  `armeabi-v7a`

    уберите отметку с **BUILD_ANDROID_PROJECTS**
 

9)	Нажмите **Configure** а затем **Generate**

10) Откройте cmd в папке со сборкой, Выполните следующие команды:

    ```
    mingw32-make -j 8

    mingw32-make install
    ```
 

#### На этом сборка завершена.

Для использования этой библиотеки в проекте Qt необходимо добавить в файл {имя проекта}.pro следующие строки: 

```
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
```

В случае сборки кроссплатформенного приложения, объединять .pro файлы из этого и предыдущего раздела следующим образом:

```
android {
    OPENCVBUILD = D:/opencv/build_for_qt_android3
    INCLUDEPATH += $$OPENCVBUILD/install/sdk/native/jni/include

    OPENCV3RDPARTYLIBS =  $$OPENCVBUILD/install/sdk/native/3rdparty/libs/armeabi-v7a
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
```
