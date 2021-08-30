#pragma once

#include <QtQuick/QQuickItem>
#include <QtCore/QObject>
#include <QtQml/qqml.h>

#include "gridoverlay.hpp"

namespace com { namespace bckmnn { namespace gridsystem {

class GridAttachedType : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int colWidth READ colWidth WRITE setColWidth NOTIFY colWidthChanged)
    QML_ANONYMOUS
public:
    GridAttachedType(QObject *parent);
    int colWidth() const;
    void setColWidth(int width);

signals:
    void colWidthChanged();
public slots:

private:
    int m_colWidth = 0;
};

class Grid : public QQuickItem
{
    Q_OBJECT
    QML_NAMED_ELEMENT(Grid)
    QML_ATTACHED(com::bckmnn::gridsystem::GridAttachedType)

    Q_PROPERTY(uint columns MEMBER m_columns NOTIFY gridChanged)
    Q_PROPERTY(double columnWidth READ getColumnWidth NOTIFY columnWidthChanged)
    Q_PROPERTY(QColor columnColor MEMBER m_column_color NOTIFY gridChanged)
    Q_PROPERTY(uint columnSpacing MEMBER m_column_spacing NOTIFY gridChanged)
    Q_PROPERTY(uint rowSpacing MEMBER m_row_spacing NOTIFY gridChanged)
    Q_PROPERTY(double contentHeight READ getContentHeight NOTIFY contentHeightChanged)
    Q_PROPERTY(bool showGrid MEMBER m_showGrid NOTIFY gridChanged)
    Q_PROPERTY(Grid* helpers READ getHelpers NOTIFY columnWidthChanged)
    Q_PROPERTY(FillStrategy fillStrategy MEMBER m_fill_strategy NOTIFY gridChanged)



public:
    enum FillStrategy
    {
        ITEM_SQUEEZE = 0,
        ITEM_BREAK
    };
    Q_ENUM(FillStrategy)

    Grid(QQuickItem *parent = nullptr);
    ~Grid() override;
    static GridAttachedType *qmlAttachedProperties(QObject *object);

    Q_INVOKABLE int getColumnStart(int column);
    Q_INVOKABLE int getColumnsWidth(int columns);

    bool showGrid();

    double getColumns();
    double getColumnWidth();
    double getContentHeight();
    QColor getColumnColor();

signals:
    void gridChanged();
    void contentHeightChanged();
    void columnWidthChanged();

public slots:
    void onGridChanged();

private:
    void calculateValues();

    Grid * getHelpers();

    double m_columns;
    double m_column_width;
    QColor m_column_color;

    double m_column_spacing;

    uint m_row_spacing;

    double m_content_height;

    FillStrategy m_fill_strategy;

    bool m_showGrid;
    GridOverlay* m_debug_overlay;

    GridAttachedType* getAttachedType(QQuickItem * item) const;

    // QQmlParserStatus interface
public:
    void componentComplete() override;

    // QQuickItem interface
protected:
    void itemChange(ItemChange, const ItemChangeData &data) override;
    void updatePolish() override;
};

}}}
