TEMPLATE = lib
TARGET = qml-gridsystem
QT += qml quick
CONFIG += plugin c++11
CONFIG += qmltypes

QML_IMPORT_NAME = com.bckmnn.gridsystem
QML_IMPORT_MAJOR_VERSION = 1

TARGET = $$qtLibraryTarget($$TARGET)
uri = com.bckmnn.gridsystem

HEADERS += \
    src/grid.hpp \
    src/gridoverlay.hpp \
    src/gridsystem_plugin.hpp

SOURCES += \
    src/grid.cpp \
    src/gridoverlay.cpp \
    src/gridsystem_plugin.cpp 

DISTFILES = qmldir \
    com_bckmnn_gridsystem.pri \
    $$PWD/README.md \
    $$PWD/LICENSE

INCLUDEPATH += src/

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
