#pragma once

#include <QGraphicsView>

class MapCanvasItem;

class MapCanvas  : public QGraphicsView
{
    Q_OBJECT

public:
    explicit MapCanvas(QWidget *parent);
    ~MapCanvas() override;

protected:
    void resizeEvent(QResizeEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    MapCanvasItem* m_MapItem;
    QPointF m_PressPos;

};
