#pragma once

#include <QMap>

#include "Core/MapConfig.h"

class MapConfiguration
{
public:
    static MapConfiguration* instance();

    void initConfiguration(int minZoom, int maxZoom);
    MapConfig* findConfig(double xspan, double viewWidth);
    
private:
    QMap<double, MapConfig> m_Zooms;
};

