#pragma once

#include <QGraphicsObject>

#include "Core/Rectangle.h"
#include "Core/MapConfig.h"

class MapCanvas;

class MapCanvasItem  : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit MapCanvasItem(MapCanvas* mapCanvas);
    ~MapCanvasItem() override;

    const QSizeF& viewSizeF() const;
    const QSize& viewSize() const;
    QRectF boundingRect() const override;
    const Rectangle& mapExtent() const;
    Rectangle& mapExtent();
    const MapConfig* mapConfig() const;

    // 事件处理
    void mapResizeViewExtent(const QSizeF& itemSize);
    void mapMoveMapExtent(const QPointF& viewOffset);
    void mapScaleMapExtent(double scaleFactor, const QPointF& scaleCenter);

    // 坐标转换
    PointXY computeViewToMap(const PointXY& p) const;

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    void updateConfig();


private:
    MapCanvas* m_MapCanvas;
    QSizeF m_ItemSize;
    Rectangle m_MapExtent;
    MapConfig* m_MapConfig;
};
