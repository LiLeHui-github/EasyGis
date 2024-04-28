#include "MapCanvasItem.h"

#include <QPainter>

#include "MapCanvas.h"
#include "MapConfiguration.h"

MapCanvasItem::MapCanvasItem(MapCanvas* mapCanvas)
    : m_MapCanvas(mapCanvas)
    , m_ItemSize(0, 0)
    , m_MapExtent(WGS84)
    , m_MapConfig(nullptr)
{
    m_MapCanvas->scene()->addItem(this);
    MapConfiguration::instance()->initConfiguration(0, 25);
}

MapCanvasItem::~MapCanvasItem()
{
    if(scene())
    {
        scene()->removeItem(this);
    }
}

const QSizeF& MapCanvasItem::viewSizeF() const
{
    return m_ItemSize;
}

const QSize& MapCanvasItem::viewSize() const
{
    return QSize{ static_cast<int>(m_ItemSize.width()), static_cast<int>(m_ItemSize.height()) };
}

QRectF MapCanvasItem::boundingRect() const
{
    return QRectF(QPointF(0, 0), viewSizeF());
}

const Rectangle& MapCanvasItem::mapExtent() const
{
    return m_MapExtent;
}

Rectangle& MapCanvasItem::mapExtent()
{
    return m_MapExtent;
}

const MapConfig* MapCanvasItem::mapConfig() const
{
    return m_MapConfig;
}

void MapCanvasItem::mapResizeViewExtent(const QSizeF& itemSize)
{
    if(m_ItemSize != itemSize)
    {
        m_ItemSize = itemSize;
        updateConfig();
    }
}

void MapCanvasItem::mapMoveMapExtent(const QPointF& viewOffset)
{
    auto old = mapExtent();
    PointXY mapOffset = PointXY{ -viewOffset.x(), viewOffset.y() };
    mapOffset *= mapConfig()->MapResolution;
    mapExtent() += mapOffset;
    mapExtent().checkRange();
    if(old != mapExtent())
    {
        updateConfig();
    }
}

void MapCanvasItem::mapScaleMapExtent(double scaleFactor, const QPointF& scaleCenter)
{
    auto old = mapExtent();
    PointXY oldCenter = mapExtent().center();
    PointXY mousePosByMap = computeViewToMap(scaleCenter);
    PointXY newCenter = PointXY{ mousePosByMap.x() + ((oldCenter.x() - mousePosByMap.x()) * scaleFactor),
                                 mousePosByMap.y() + ((oldCenter.y() - mousePosByMap.y()) * scaleFactor) };
    mapExtent().scale(scaleFactor, &newCenter);
    mapExtent().checkRange();
    if (old != mapExtent())
    {
        updateConfig();
    }
}

PointXY MapCanvasItem::computeViewToMap(const PointXY& p) const
{
    const PointXY& leftTop = WGS84.leftTop();
    return  PointXY{ leftTop.x() + p.x() * mapConfig()->MapResolution, leftTop.y() - p.y() * mapConfig()->MapResolution };
}

void MapCanvasItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setRenderHint(QPainter::Antialiasing);

    QString message;
    message += mapExtent().toString();
    painter->drawText(boundingRect(), message, QTextOption(Qt::AlignCenter));
}

void MapCanvasItem::updateConfig()
{
    m_MapConfig = MapConfiguration::instance()->findConfig(mapExtent().width() / viewSizeF().width(), viewSizeF().width());

    const PointXY& center = mapExtent().center();
    double newWidth = m_MapConfig->MapResolution * viewSizeF().width();
    double newHeight = m_MapConfig->MapResolution * viewSizeF().height();
    mapExtent().set(center, newWidth, newHeight);

    update();
}
