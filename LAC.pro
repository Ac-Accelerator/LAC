QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES += GSL_DLL
#PRE_TARGETDEPS += D:/msys64/mingw64/lib/libgslcblas.a
#PRE_TARGETDEPS += D:/msys64/mingw64/lib/libgsl.a

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    base.cpp \
    calculate.cpp \
    determinant.cpp \
    editor.cpp \
    fraction.cpp \
    main.cpp \
    mainwindow.cpp \
    matix.cpp \
    size_check.cpp

HEADERS += \
    base.h \
    calculate.h \
    determinant.h \
    editor.h \
    fraction.h \
    mainwindow.h \
    matix.h \
    size_check.h

FORMS += \
    editor.ui \
    mainwindow.ui \
    size_check.ui

RC_ICONS=math.ico
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
