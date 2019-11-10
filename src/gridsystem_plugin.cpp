#include "grid.h"
#include "gridoverlay.h"
#include "gridsystem_plugin.h"

#include <qqml.h>

void GridsystemPlugin::registerTypes(const char *uri)
{
    // @uri com.bckmnn.gridsystem
    qmlRegisterType<com::bckmnn::gridsystem::GridAttachedType>();
    qmlRegisterType<com::bckmnn::gridsystem::Grid>(uri, 1, 0, "Grid");
}
