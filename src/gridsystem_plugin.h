#ifndef GRIDSYSTEM_PLUGIN_H
#define GRIDSYSTEM_PLUGIN_H

#include <QQmlExtensionPlugin>

class GridsystemPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri) override;

};

#endif // GRIDSYSTEM_PLUGIN_H

