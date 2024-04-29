#pragma once

#include <QSharedPointer>
#include <QImage>

struct MapConfig
{
    // 地图层级
    int ZoomLevel;

    // 瓦片横向/纵向数量
    int TileCount;

    // 地图宽度(像素)
    double ViewWidth;

    // 地图分辨率(m/每像素)
    double MapResolution;

    // 单个瓦片宽度(m)
    double TileUnitWidth;
};


struct TileRequest
{
    double px;
    double py;
    QString url;
};

using TileRequests = QVector<TileRequest>;

struct TileResponse
{
    double px;
    double py;
    QImage image;
};

using TileResponsePtr = QSharedPointer<TileResponse>;

