#-------------------------------------------------
#
# Project created by QtCreator 2018-12-07T10:38:15
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImgLabel
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
        mainwindow.cpp \
    mylabel.cpp \
    mycamwidget.cpp

HEADERS += \
        mainwindow.h \
    mylabel.h \
    mycamwidget.h

FORMS += \
        mainwindow.ui

# 导入opencv的路径
INCLUDEPATH += /usr/local/include/
# 导入opencv的完整库
#LIBS += -L/usr/local/lib \
#        -lopencv_highgui \
#        -lopencv_core \
#        -lopencv_imgproc \
#        -lopencv_imgcodecs
#LIBS += `pkg-config opencv --cflags --libs`
#LIBS += /usr/local/lib/libopencv_imgproc.so /usr/local/lib/libopencv_core.so
LIBS += -L/usr/local/lib \
    -lopencv_calib3d \
    #-lopencv_contrib \
    -lopencv_core \
    -lopencv_features2d \
    -lopencv_flann \
    #-lopencv_gpu \
    -lopencv_highgui \
    -lopencv_imgproc \
    #-lopencv_legacy \
    -lopencv_ml \
    #-lopencv_nonfree \
    -lopencv_objdetect \
    #-lopencv_ocl \
    -lopencv_photo \
    -lopencv_stitching \
    #-lopencv_superres \
    -lopencv_video \
    #-lopencv_videostab \
    -lopencv_videoio \
    -lopencv_imgcodecs \

LIBS += -lpthread

RESOURCES += \
    icon.qrc

