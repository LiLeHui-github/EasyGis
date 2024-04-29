#include "WMSTileLayer.h"

#include "MapCanvas/MapCanvasItem.h"
#include "TileLoaderService.h"

int clamp(int val, int min, int max)
{
    return std::max(min, std::min(max, val));
}

WMSTileLayer::WMSTileLayer(const QString& url, MapCanvasItem* map)
    : BaseLayer(map)
    , m_Url(url)
{
}

QString WMSTileLayer::type() const
{
    return "WMSTile";
}

void WMSTileLayer::render(QPainter* painter)
{
    BaseLayer::render(painter);
}

void WMSTileLayer::updateLayer()
{
    createXyzTileResquests();
}

void WMSTileLayer::createXyzTileResquests()
{
    int zoomLevel = map()->mapConfig()->ZoomLevel;
    double tileUnitWidth = map()->mapConfig()->TileUnitWidth;
    PointXY leftTop = WGS84.leftTop();

    int minCount = 0;
    int maxCount = map()->mapConfig()->TileCount - 1;

    double col0 = mapMinOffset().x() / tileUnitWidth;
    double row0 = mapMinOffset().y() / tileUnitWidth;
    double col1 = mapMaxOffset().x() / tileUnitWidth;
    double row1 = mapMaxOffset().y() / tileUnitWidth;

    int minCol = clamp(std::floor(col0), minCount, maxCount);
    int minRow = clamp(std::floor(row0), minCount, maxCount);
    int maxCol = clamp(std::floor(col1), minCount, maxCount);
    int maxRow = clamp(std::floor(row1), minCount, maxCount);

    //QString text;
    //text += QString{ u8"col0: %1 " }.arg(minCol);
    //text += QString{ u8"row0: %1 " }.arg(minRow);
    //text += QString{ u8"col1: %1 " }.arg(maxCol);
    //text += QString{ u8"row1: %1 " }.arg(maxRow);

    //QPainter painter(&m_Image);
    //painter.drawText(QPointF{ 100, 100 }, text);

    TileRequests requests;
    for(int x = minCol; x <= maxCol; ++x)
    {
        for(int y = minRow; y <= maxRow; ++y)
        {
            PointXY pos = PointXY{ leftTop.x() + x * tileUnitWidth, leftTop.y() - y * tileUnitWidth };
            QString url = m_Url.arg(zoomLevel).arg(x).arg(y);
            requests << TileRequest{ pos.x(), pos.y(), url };
        }
    }

    TileLoaderService::instance()->execute(requests, m_Image.size(), map());
    m_Image = TileLoaderService::instance()->getContext();
}
