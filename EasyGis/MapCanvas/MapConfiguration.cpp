#include "MapConfiguration.h"

#include "Core/PointXY.h"
#include "Core/Rectangle.h"

MapConfiguration* MapConfiguration::instance()
{
    static MapConfiguration configuration;
    return &configuration;
}

void MapConfiguration::initConfiguration(int minZoom, int maxZoom)
{
    m_Zooms.clear();

    for(int zoom = minZoom; zoom <= maxZoom; ++zoom)
    {
        MapConfig config;
        config.ZoomLevel = zoom;
        config.TileCount = 2 << zoom;
        config.ViewWidth = config.TileCount * 256.0;
        config.MapResolution = WGS84.width() / config.ViewWidth;
        config.TileUnitWidth = config.MapResolution * 256.0;
        m_Zooms.insert(config.MapResolution, config);
    }
}

MapConfig* MapConfiguration::findConfig(double xspan, double viewWidth)
{
    auto it = m_Zooms.begin();
    auto prev = it;

    while(it != m_Zooms.end() && it.key() < xspan)
    {
        prev = it;
        ++it;
    }

    if(it == m_Zooms.end() || it != m_Zooms.end() && it.key() - xspan > xspan - prev.key())
    {
        it = prev;
    }

    while (it != m_Zooms.end() && it.value().ViewWidth < viewWidth)
    {
        --it;
    }

    return &it.value();

}
