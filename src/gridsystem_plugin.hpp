#pragma once

#include <QtQml/QQmlEngine>
#include <QtQml/QQmlEngineExtensionPlugin>

class GridsystemPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:


    // QQmlTypesExtensionInterface interface
public:
    void registerTypes(const char *uri) override;
};


