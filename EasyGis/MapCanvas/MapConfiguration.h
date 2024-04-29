#pragma once

#include <QMap>

#include "Core/MapDefines.h"

class MapConfiguration
{
public:
    static MapConfiguration* instance();

    void initConfiguration(int minZoom, int maxZoom);
    const MapConfig* findConfig(double xspan, double viewWidth);
    
private:
    QMap<double, MapConfig> m_Zooms;
};

