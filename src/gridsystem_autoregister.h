#ifndef GRIDSYSTEM_AUTOREG_H
#define GRIDSYSTEM_AUTOREG_H

#include <QtCore/QCoreApplication>
#include <QtQml/QQmlEngine>

#include "grid.h"

namespace com { namespace bckmnn { namespace gridsystem {

static const char* GRIDSYSTEM_NS = "com.bckmnn.gridsystem";

static void registerTypes()
{
    qmlRegisterType<GridAttachedType>();
    qmlRegisterType<Grid>(GRIDSYSTEM_NS, 1, 0, "GSGrid");
}

Q_COREAPP_STARTUP_FUNCTION(registerTypes)

} } }

#endif // GRIDSYSTEM_AUTOREG_H
