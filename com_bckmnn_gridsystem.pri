RESOURCES += \
    $$PWD/com_bckmnn_qml-gridsystem.qrc

!contains(GRIDSYSTEM_CONFIG,"noautoregister") {
    DEFINES += GRIDSYSTEM_AUTO_REGISTER
}

HEADERS += \
    $$PWD/src/grid.h \
    $$PWD/src/gridoverlay.h \
    $$PWD/src/gridsystem_autoregister.h

SOURCES += \
    $$PWD/src/grid.cpp \
    $$PWD/src/gridoverlay.cpp

DISTFILES += \
    $$PWD/README.md \
    $$PWD/LICENSE
