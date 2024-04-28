#pragma once

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