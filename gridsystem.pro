TEMPLATE = lib
TARGET = GridSystem
QT += qml quick
CONFIG += plugin c++11

TARGET = $$qtLibraryTarget($$TARGET)
uri = com.bckmnn.gridsystem

HEADERS += \
    src/grid.h \
    src/gridoverlay.h \
    src/gridsystem_plugin.h 

SOURCES += \
    src/grid.cpp \
    src/gridoverlay.cpp \
    src/gridsystem_plugin.cpp 

DISTFILES = qmldir \
    com_bckmnn_gridsystem.pri \
    $$PWD/README.md \
    $$PWD/LICENSE

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}
