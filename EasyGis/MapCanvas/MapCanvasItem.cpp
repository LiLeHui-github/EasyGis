#include "MapCanvasItem.h"

#include <QTimer>
#include <QPainter>

#include "MapCanvas.h"
#include "MapConfiguration.h"
#include "Layer/BaseLayer.h"

MapCanvasItem::MapCanvasItem(MapCanvas* mapCanvas)
    : m_MapCanvas(mapCanvas)
    , m_ItemSize(0, 0)
    , m_MapExtent(WGS84)
    , m_MapConfig(nullptr)
    , m_UpdateTimer(new QTimer(this))
{
    m_MapCanvas->scene()->addItem(this);
    MapConfiguration::instance()->initConfiguration(0, 25);

    connect(m_UpdateTimer, &QTimer::timeout, this, &MapCanvasItem::timerTimeOut);
    m_UpdateTimer->start(1000.0 / 45.0);
}

MapCanvasItem::~MapCanvasItem()
{
    if(scene())
    {
        scene()->removeItem(this);
    }

    m_UpdateTimer->stop();
}

const QSizeF& MapCanvasItem::viewSizeF() const
{
    return m_ItemSize;
}

const QSize& MapCanvasItem::viewSize() const
{
    return std::move(QSize{ static_cast<int>(m_ItemSize.width()), static_cast<int>(m_ItemSize.height()) });
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

PointXY MapCanvasItem::mapLeftTop() const
{
    return mapExtent().leftTop();
}

PointXY MapCanvasItem::mapRightBottom() const
{
    return mapExtent().rightBottom();
}

PointXY MapCanvasItem::mapMinOffset() const
{
    const PointXY& leftTop = WGS84.leftTop();
    return PointXY{ mapLeftTop().x() - leftTop.x(), leftTop.y() - mapLeftTop().y() };
}

PointXY MapCanvasItem::mapMaxOffset() const
{
    const PointXY& leftTop = WGS84.leftTop();
    return PointXY{ mapRightBottom().x() - leftTop.x(), leftTop.y() - mapRightBottom().y() };
}

void MapCanvasItem::addLayer(BaseLayer* layer, bool autoDelete)
{
    removeLayer(layer);
    layer->setAutoDelete(autoDelete);
    m_Layers.insert(layer->id(), layer);
}

void MapCanvasItem::removeLayer(BaseLayer* layer)
{
    auto it = m_Layers.find(layer->id());
    if(it != m_Layers.end())
    {
        if(it.value()->autoDelete())
        {
            delete it.value();
        }
        m_Layers.erase(it);
    }
}

BaseLayer* MapCanvasItem::layer(const QString& id) const
{
    auto it = m_Layers.find(id);
    if (it != m_Layers.end())
    {
        return it.value();
    }
    return nullptr;
}

void MapCanvasItem::mapResizeViewExtent(const QSizeF& itemSize)
{
    if(m_ItemSize != itemSize)
    {
        m_ItemSize = itemSize;
        updateMap();
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
        updateMap();
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
        updateMap();
    }
}

PointXY MapCanvasItem::computeViewToMap(const PointXY& p) const
{
    const PointXY& mapLeftTop = mapExtent().leftTop();
    return  PointXY{ mapLeftTop.x() + p.x() * mapConfig()->MapResolution, mapLeftTop.y() - p.y() * mapConfig()->MapResolution };
}

PointXY MapCanvasItem::computeMapToView(const PointXY& p) const
{
    const PointXY& mapLeftTop = mapExtent().leftTop();
    return PointXY{ (p.x() - mapLeftTop.x()) / mapConfig()->MapResolution,
                    (mapLeftTop.y() - p.y()) / mapConfig()->MapResolution };
}

void MapCanvasItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setRenderHint(QPainter::Antialiasing);

    for (BaseLayer* layer : m_Layers)
    {
        layer->render(painter);
    }

    QString message;
    message += mapExtent().toString();
    painter->drawText(boundingRect(), message, QTextOption(Qt::AlignCenter));
}

void MapCanvasItem::timerTimeOut()
{
    update();
}

void MapCanvasItem::updateMap()
{
    double mapWidth = mapExtent().width();
    double viewWidth = viewSizeF().width();
    m_MapConfig = MapConfiguration::instance()->findConfig(mapWidth / viewWidth, viewWidth);

    const PointXY& center = mapExtent().center();
    double newWidth = m_MapConfig->MapResolution * viewSizeF().width();
    double newHeight = m_MapConfig->MapResolution * viewSizeF().height();
    mapExtent().set(center, newWidth, newHeight);

    for(BaseLayer* layer : m_Layers)
    {
        layer->update();
    }
}
