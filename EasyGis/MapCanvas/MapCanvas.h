#pragma once

#include <QGraphicsView>

class MapCanvas  : public QGraphicsView
{
    Q_OBJECT

public:
    MapCanvas(QWidget *parent);
    ~MapCanvas();
};
