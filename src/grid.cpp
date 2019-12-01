#include <QDebug>
#include <QtMath>

#include "grid.h"

#if defined(GRIDSYSTEM_AUTO_REGISTER)
#include "gridsystem_autoregister.h"
#endif

namespace com { namespace bckmnn { namespace gridsystem {

GridAttachedType *Grid::qmlAttachedProperties(QObject *object)
{
    return new GridAttachedType(object);
}

GridAttachedType::GridAttachedType(QObject *parent): QObject(parent), m_colWidth(0)
{
}

int GridAttachedType::colWidth() const
{
    return m_colWidth;
}

void GridAttachedType::setColWidth(int width)
{
    m_colWidth = width;
    emit colWidthChanged();
}

Grid::Grid(QQuickItem *parent):
    QQuickItem(parent),
    m_columns(12.0),
    m_column_width(0),
    m_column_color("#3Cff0000"),
    m_column_spacing(20.0),
    m_row_spacing(0),
    m_fill_strategy(ITEM_BREAK),
    m_showGrid(false)
{
    m_debug_overlay = new GridOverlay(this);
    m_debug_overlay->setParentItem(this);
    m_debug_overlay->setZ(1000);
    m_debug_overlay->setVisible(false);
    connect(this, &QQuickItem::widthChanged, this, &Grid::onGridChanged);
    connect(this, &Grid::gridChanged, this, &Grid::onGridChanged);
}

Grid::~Grid()
{

}

int Grid::getColumnStart(int column)
{
    if(column <= 0){
        return 0;
    }
    return qFloor(static_cast<double>(column)*(m_column_width+m_column_spacing));
}

int Grid::getColumnsWidth(int columns)
{
    if(columns <= 0){
        return 0;
    }
    return qFloor(static_cast<double>(columns)*(m_column_width+m_column_spacing)-m_column_spacing);
}

double Grid::getColumns()
{
    return m_columns;
}

void Grid::onGridChanged()
{
    calculateValues();
    m_debug_overlay->setVisible(m_showGrid);
}

void Grid::calculateValues()
{
    int full_width = static_cast<int>(this->width());
    int gutters_width = static_cast<int>((m_columns - 1) * m_column_spacing);
    int avilable_columns_width = full_width - gutters_width;
    m_column_width = avilable_columns_width/m_columns;
    emit columnWidthChanged();
}

double Grid::getColumnWidth()
{
    return m_column_width;
}

double Grid::getContentHeight()
{
    return m_content_height;
}

QColor Grid::getColumnColor()
{
    return m_column_color;
}

bool Grid::showGrid()
{
    return m_showGrid;
}

Grid *Grid::getHelpers()
{
    return this;
}

GridAttachedType *Grid::getAttachedType(QQuickItem *item) const
{
    return qobject_cast<GridAttachedType *> (qmlAttachedPropertiesObject<Grid> (item, false));
}

void Grid::componentComplete()
{
    QQuickItem::componentComplete ();
    connect (this, &Grid::widthChanged,   this, &Grid::polish, Qt::UniqueConnection);
    connect (this, &Grid::heightChanged,  this, &Grid::polish, Qt::UniqueConnection);
    connect (this, &Grid::gridChanged, this, &Grid::polish, Qt::UniqueConnection);
    polish();
}

void Grid::itemChange(QQuickItem::ItemChange change, const QQuickItem::ItemChangeData & data)
{
    QQuickItem::itemChange (change, data);
    switch (int (change)) {
        case ItemChildAddedChange: {
            if (QQuickItem * child { data.item }) {
                connect (child, &QQuickItem::visibleChanged,        this, &Grid::polish, Qt::UniqueConnection);
                connect (child, &QQuickItem::implicitWidthChanged,  this, &Grid::polish, Qt::UniqueConnection);
                connect (child, &QQuickItem::implicitHeightChanged, this, &Grid::polish, Qt::UniqueConnection);
                if (const GridAttachedType * attached { getAttachedType (child) }) {
                    connect (attached, &GridAttachedType::colWidthChanged, this, &Grid::polish, Qt::UniqueConnection);
                }
                polish ();
            }
            break;
        }
        case ItemChildRemovedChange: {
            if (QQuickItem * child { data.item }) {
                disconnect (child, Q_NULLPTR, this, Q_NULLPTR);
                if (const GridAttachedType * attached { getAttachedType (child) }) {
                    disconnect (attached, Q_NULLPTR, this, Q_NULLPTR);
                }
                polish ();
            }
            break;
        }
    }
}

void Grid::updatePolish()
{
    QQuickItem::updatePolish();
    const QList<QQuickItem *> childItemsList { childItems () };
    QVector<QQuickItem *> layoutItemsList { };
    layoutItemsList.reserve (childItemsList.count ());
    for(QQuickItem * child : childItemsList){
        const GridAttachedType* attached = getAttachedType(child);
        if(child->isVisible() && attached){
            layoutItemsList.append(child);
        }
    }
    int yOffset = 0;
    int maxY = 0;
    int columns_used = 0;
    for (QQuickItem * child : layoutItemsList) {
        const GridAttachedType* attached = getAttachedType(child);
        if (attached && attached->colWidth() > 0) {
            int columns_requested = attached->colWidth();
            switch (m_fill_strategy) {
            case Grid::FillStrategy::ITEM_SQUEEZE:
                child->setX(getColumnStart(columns_used));
                child->setY(yOffset);
                if(columns_used + columns_requested > m_columns){
                    qWarning() << "item requested" << columns_requested << "columns. but only" << m_columns-columns_used << "are available. item will be squeezed.";
                    child->setWidth(getColumnsWidth(static_cast<int>(m_columns-columns_used)));
                    columns_used += static_cast<int>(m_columns-columns_used);
                }else{
                    child->setWidth(getColumnsWidth(columns_requested));
                    columns_used += columns_requested;
                }
                if(child->height() > maxY){
                    maxY = qFloor(child->height());
                }
                if(columns_used >= m_columns){
                    yOffset += maxY + static_cast<int>(m_row_spacing);
                    maxY = 0;
                    columns_used = 0;
                }
                break;
            case Grid::FillStrategy::ITEM_BREAK:
                if(columns_used + columns_requested > m_columns){
                    if(columns_requested > m_columns){
                        qWarning() << "item requested" << columns_requested << "columns. but grid has only" << m_columns << "columns. item will be ignored.";
                    }else{
                        yOffset += maxY + static_cast<int>(m_row_spacing);
                        maxY = 0;
                        columns_used = 0;
                        child->setX(getColumnStart(columns_used));
                        child->setY(yOffset);
                        child->setWidth(getColumnsWidth(columns_requested));
                        columns_used += columns_requested;
                    }
                }else{
                    child->setX(getColumnStart(columns_used));
                    child->setY(yOffset);
                    child->setWidth(getColumnsWidth(columns_requested));
                    columns_used += columns_requested;
                }
                if(child->height() > maxY){
                    maxY = qFloor(child->height());
                }
                if(columns_used >= m_columns){
                    yOffset += maxY + static_cast<int>(m_row_spacing);
                    maxY = 0;
                    columns_used = 0;
                }
                break;
            }


        }
    }
    m_content_height = yOffset + maxY;
    emit contentHeightChanged();
}

}}}
