#ifndef GRIDOVERLAY_H
#define GRIDOVERLAY_H

#include <QObject>
#include <QQuickItem>

namespace com { namespace bckmnn { namespace gridsystem {

class Grid;

class GridOverlay : public QQuickItem
{
    Q_OBJECT
public:
    GridOverlay(QQuickItem *parent = nullptr);
    ~GridOverlay() override;
signals:

public slots:
    void onGridChanged();
    // QQuickItem interface
protected:
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *updatePaintNodeData) override;
    Grid *m_grid = nullptr;
};

}}}

#endif // GRIDOVERLAY_H
