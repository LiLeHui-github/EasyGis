#include "WMSTileLayer.h"

#include "MapCanvas/MapCanvasItem.h"

int clamp(int val, int min, int max)
{
    return std::max(min, std::min(max, val));
}

WMSTileLayer::WMSTileLayer(MapCanvasItem* map)
    : BaseLayer(map)
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
    int minCount = 0;
    int maxCount = map()->mapConfig()->TileCount - 1;

    double col0 = mapMinOffset().x() / map()->mapConfig()->TileUnitWidth;
    double row0 = mapMinOffset().y() / map()->mapConfig()->TileUnitWidth;
    double col1 = mapMaxOffset().x() / map()->mapConfig()->TileUnitWidth;
    double row1 = mapMaxOffset().y() / map()->mapConfig()->TileUnitWidth;

    int minCol = clamp(std::floor(col0), minCount, maxCount);
    int minRow = clamp(std::floor(row0), minCount, maxCount);
    int maxCol = clamp(std::floor(col1), minCount, maxCount);
    int maxRow = clamp(std::floor(row1), minCount, maxCount);

    QString text;
    text += QString{ u8"col0: %1 " }.arg(minCol);
    text += QString{ u8"row0: %1 " }.arg(minRow);
    text += QString{ u8"col1: %1 " }.arg(maxCol);
    text += QString{ u8"row1: %1 " }.arg(maxRow);

    QPainter painter(&m_Image);
    painter.drawText(QPointF{ 100, 100 }, text);

}
