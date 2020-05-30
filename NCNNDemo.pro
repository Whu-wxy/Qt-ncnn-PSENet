#-------------------------------------------------
#
# Project created by QtCreator 2020-05-18T12:13:54
#
#-------------------------------------------------

QT       += core gui androidextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NCNNDemo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        ncnndlg.cpp \
    imgutils.cpp \
    androidsetup.cpp \
    detector.cpp

HEADERS += \
        ncnndlg.h \
    imgutils.h \
    androidsetup.h \
    detector.h

CONFIG += mobility
MOBILITY =


#openmp
#QMAKE_CFLAGS += -fopenmp
QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS += -fopenmp
LIBS += -fopenmp -lgomp

#INCLUDEPATH += D:\ncnn-android-lib\ncnn-android-lib\include \
#    D:\ncnn-android-lib\ncnn-android-lib\include\ncnn

#LIBS += -L$$PWD/../../ncnn-android-lib/ncnn-android-lib/armeabi-v7a/ -lncnn

#INCLUDEPATH += $$PWD/../../ncnn-android-lib/ncnn-android-lib/armeabi-v7a
#DEPENDPATH += $$PWD/../../ncnn-android-lib/ncnn-android-lib/armeabi-v7a

#PRE_TARGETDEPS += $$PWD/../../ncnn-android-lib/ncnn-android-lib/armeabi-v7a/libncnn.a

LIBS += -L$$PWD/../../ncnn-lib/lib/ -lncnn

INCLUDEPATH += $$PWD/../../ncnn-lib/include
DEPENDPATH += $$PWD/../../ncnn-lib/include

PRE_TARGETDEPS += $$PWD/../../ncnn-lib/lib/libncnn.a



android {
ANDROID_OPENCV = D:/OpenCV-android-sdk/sdk/native

INCLUDEPATH += \
$$ANDROID_OPENCV/jni/include/opencv    \
$$ANDROID_OPENCV/jni/include/opencv2    \
$$ANDROID_OPENCV/jni/include            \


LIBS += $$ANDROID_OPENCV/libs/armeabi-v7a/libopencv_java3.so \
$$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_ml.a \
$$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_objdetect.a \
$$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_calib3d.a \
#$$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_video.a \
$$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_features2d.a \
#$$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_highgui.a \
#$$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_dnn.a  \
$$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_flann.a \
$$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_imgproc.a \
$$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_core.a     \
$$ANDROID_OPENCV/3rdparty/libs/armeabi-v7a/libIlmImf.a  \
$$ANDROID_OPENCV/3rdparty/libs/armeabi-v7a/liblibjpeg-turbo.a \
#$$ANDROID_OPENCV/3rdparty/libs/armeabi-v7a/liblibpng.a \
#$$ANDROID_OPENCV/3rdparty/libs/armeabi-v7a/liblibtiff.a \
#$$ANDROID_OPENCV/3rdparty/libs/armeabi-v7a/liblibjasper.a \
#$$ANDROID_OPENCV/3rdparty/libs/armeabi-v7a/libtbb.a \

data.files += src/psenet_lite_mbv2.bin
data.files += src/psenet_lite_mbv2.param
data.files += src/test.jpg
data.path = /assets/dst/
INSTALLS += data


LIBS += -landroid
}

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_EXTRA_LIBS = \
        $$PWD/../../../OpenCV-android-sdk/sdk/native/libs/armeabi-v7a/libopencv_java3.so
}

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/src/com/amin/NCNNDemo/NCNNDemo.java

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

RESOURCES += \
    src.qrc

