#pragma once

#include <QGraphicsObject>

#include "Core/Rectangle.h"
#include "Core/MapConfig.h"

class QTimer;
class MapCanvas;
class BaseLayer;

class MapCanvasItem  : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit MapCanvasItem(MapCanvas* mapCanvas);
    ~MapCanvasItem() override;

    // �ӿڷ�Χ����
    const QSizeF& viewSizeF() const;
    const QSize& viewSize() const;
    QRectF boundingRect() const override;
    const Rectangle& mapExtent() const;
    Rectangle& mapExtent();
    const MapConfig* mapConfig() const;

    // �ӿڷ�Χ����
    PointXY mapLeftTop() const;
    PointXY mapRightBottom() const;
    PointXY mapMinOffset() const;
    PointXY mapMaxOffset() const;

    // ͼ�����
    void addLayer(BaseLayer* layer, bool autoDelete = true);
    void removeLayer(BaseLayer* layer);
    BaseLayer* layer(const QString& id) const;

    // �¼�����
    void mapResizeViewExtent(const QSizeF& itemSize);
    void mapMoveMapExtent(const QPointF& viewOffset);
    void mapScaleMapExtent(double scaleFactor, const QPointF& scaleCenter);

    // ����ת��
    PointXY computeViewToMap(const PointXY& p) const;
    PointXY computeMapToView(const PointXY& p) const;

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    void timerTimeOut();
    void updateMap();

private:
    MapCanvas* m_MapCanvas;
    QSizeF m_ItemSize;
    Rectangle m_MapExtent;
    const MapConfig* m_MapConfig;
    QTimer* m_UpdateTimer;
    QMap<QString, BaseLayer*> m_Layers;
};
