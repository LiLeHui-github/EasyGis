#include "BaseLayer.h"

#include "MapCanvas/MapCanvasItem.h"

BaseLayer::BaseLayer(MapCanvasItem* map)
    : m_AutoDelte(false)
    , m_Map(map)
{
}

BaseLayer::~BaseLayer()
{
}

void BaseLayer::setId(const QString& id)
{
    m_Id = id;
}

QString BaseLayer::id() const
{
    return m_Id;
}

void BaseLayer::setAutoDelete(bool autoDelete)
{
    m_AutoDelte = autoDelete;
}

bool BaseLayer::autoDelete() const
{
    return m_AutoDelte;
}

MapCanvasItem* BaseLayer::map() const
{
    return m_Map;
}

PointXY BaseLayer::mapLeftTop() const
{
    return map()->mapLeftTop();
}

PointXY BaseLayer::mapRightBottom() const
{
    return map()->mapRightBottom();
}

PointXY BaseLayer::mapMinOffset() const
{
    return map()->mapMinOffset();
}

PointXY BaseLayer::mapMaxOffset() const
{
    return map()->mapMaxOffset();
}

QSize BaseLayer::layerSize() const
{
    return map()->viewSize();
}

PointXY BaseLayer::computeViewToMap(const PointXY& p) const
{
    return map()->computeViewToMap(p);
}

PointXY BaseLayer::computeMapToView(const PointXY& p) const
{
    return map()->computeMapToView(p);
}

void BaseLayer::update()
{
    m_Image = QImage{ map()->viewSize(), QImage::Format_ARGB32_Premultiplied };
    m_Image.fill(Qt::transparent);
    updateLayer();
}

void BaseLayer::render(QPainter* painter)
{
    painter->drawImage(QPointF{ 0, 0 }, m_Image);
}

