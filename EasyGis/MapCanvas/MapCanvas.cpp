#include "MapCanvas.h"

#include <QMouseEvent>
#include <QGraphicsScene>

#include "MapCanvasItem.h"
#include "Layer/WMSTileLayer.h"

MapCanvas::MapCanvas(QWidget *parent)
    : QGraphicsView(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QGraphicsScene* scene = new QGraphicsScene(this);
    setScene(scene);

    QSizeF size = viewport()->size();
    scene->setSceneRect(QRectF(0, 0, size.width(), size.height()));
    this->setSceneRect(QRectF(0, 0, size.width(), size.height()));

    m_MapItem = new MapCanvasItem(this);
    m_MapItem->mapResizeViewExtent(size);

    WMSTileLayer* wmsLayer = new WMSTileLayer(QString{ u8"E:/BaiduNetdiskDownload/MapTile/%1/%2/%3.jpg" }, m_MapItem);
    wmsLayer->setId(createUid());
    m_MapItem->addLayer(wmsLayer);
}

MapCanvas::~MapCanvas()
{
    
}

void MapCanvas::resizeEvent(QResizeEvent* event)
{
    QSizeF size = viewport()->size();
    scene()->setSceneRect(QRectF(0, 0, size.width(), size.height()));
    this->setSceneRect(QRectF(0, 0, size.width(), size.height()));
    m_MapItem->mapResizeViewExtent(size);
    QGraphicsView::resizeEvent(event);
}

void MapCanvas::wheelEvent(QWheelEvent* event)
{
    if(event->delta() > 0)
    {
        m_MapItem->mapScaleMapExtent(1.0 / 2.0, event->pos());
    }
    else
    {
        m_MapItem->mapScaleMapExtent(2.0, event->pos());
    }
    QGraphicsView::wheelEvent(event);
}

void MapCanvas::mousePressEvent(QMouseEvent* event)
{
    m_PressPos = event->pos();
    QGraphicsView::mousePressEvent(event);
}

void MapCanvas::mouseMoveEvent(QMouseEvent* event)
{
    QPointF curPos = event->pos();
    QPointF offset = curPos - m_PressPos;
    m_PressPos = curPos;

    if(event->isAccepted())
    {
        m_MapItem->mapMoveMapExtent(offset);
    }

    QGraphicsView::mouseMoveEvent(event);
}
