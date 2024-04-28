#pragma once

#include "BaseLayer.h"

class WMSTileLayer : public BaseLayer
{
public:
    explicit WMSTileLayer(MapCanvasItem* map);

    QString type() const override;

protected:
    void render(QPainter* painter) override;
    void updateLayer() override;

private:
    void createXyzTileResquests();

};

