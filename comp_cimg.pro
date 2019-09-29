TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../CImg
unix {
    INCLUDEPATH += /home/carlo/lib/swipl/include
    LIBS += -L/home/carlo/lib/swipl/lib/x86_64-linux -lswipl
    LIBS += -lX11 -lpthread
}

SOURCES += \
        main.cpp \
    swipl_cimg.cpp

HEADERS += \
    swipl_cimg.h

DISTFILES += \
    example.pl
