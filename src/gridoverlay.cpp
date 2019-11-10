#include <QSGFlatColorMaterial>
#include <QSGGeometryNode>

#include "gridoverlay.h"
#include "grid.h"

namespace com { namespace bckmnn { namespace gridsystem {

GridOverlay::GridOverlay(QQuickItem *parent):
    QQuickItem(parent)
{
    setFlag(QQuickItem::ItemHasContents, true);
    Grid* g = qobject_cast<Grid*>(parent);
    if(g != nullptr){
        m_grid = g;
        connect (m_grid, &Grid::gridChanged,    this, &GridOverlay::onGridChanged, Qt::UniqueConnection);
        connect (m_grid, &Grid::widthChanged,   this, &GridOverlay::onGridChanged, Qt::UniqueConnection);
        connect (m_grid, &Grid::heightChanged,  this, &GridOverlay::onGridChanged, Qt::UniqueConnection);
    }
}

GridOverlay::~GridOverlay()
{
    if(m_grid){
        disconnect(m_grid, Q_NULLPTR, this, Q_NULLPTR);
    }
}

void GridOverlay::onGridChanged()
{
    update();
}


QSGNode *GridOverlay::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *updatePaintNodeData)
{
    Q_UNUSED(updatePaintNodeData)
    if(m_grid){
        QSGGeometryNode *node = nullptr;
        QSGGeometry *geometry = nullptr;
        QSGGeometry::Point2D *vertices;
        QSGFlatColorMaterial *material;

        int points = static_cast<int>(m_grid->getColumns())*4;

        if (!oldNode)
        {
            node = new QSGGeometryNode;
            geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), points);
            geometry->setVertexDataPattern(QSGGeometry::DynamicPattern);
            geometry->setDrawingMode(GL_QUADS);
            node->setGeometry(geometry);
            node->setFlag(QSGNode::OwnsGeometry);
            material = new QSGFlatColorMaterial;
            material->setColor(m_grid->getColumnColor());
            node->setMaterial(material);
            node->setFlag(QSGNode::OwnsMaterial);
        }
        else
        {
            node = static_cast<QSGGeometryNode *>(oldNode);
            geometry = node->geometry();
            geometry->allocate(points);
        }

        vertices = geometry->vertexDataAsPoint2D();

        if(m_grid->showGrid()){
            int ys = 0;
            float xe = static_cast<float>(m_grid->getColumnWidth());
            float ye = static_cast<float>(m_grid->height());
            for(int i = 0; i < m_grid->getColumns(); i++)
            {
                float xs = m_grid->getColumnStart(i);
                vertices[(4*i)].set(xs, ys);
                vertices[(4*i)+1].set(xs, ye);
                vertices[(4*i)+2].set(xs+xe, ye);
                vertices[(4*i)+3].set(xs+xe, ys);
            }
        }
        geometry->markVertexDataDirty();
        node->markDirty(QSGNode::DirtyGeometry | QSGNode::DirtyMaterial);
        return node;
    }else{
        return new QSGGeometryNode;
    }
}
}}}