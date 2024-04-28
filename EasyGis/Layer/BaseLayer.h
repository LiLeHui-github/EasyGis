#pragma once

#include <QObject>
#include <QUuid>
#include <QPainter>

#include "Core/PointXY.h"

class MapCanvasItem;

class BaseLayer : public QObject
{
    Q_OBJECT
public:
    explicit BaseLayer(MapCanvasItem* map);
    ~BaseLayer() override;

    void setId(const QString& id);
    QString id() const;

    void setAutoDelete(bool autoDelete);
    bool autoDelete() const;

    MapCanvasItem* map() const;
    PointXY mapLeftTop() const;
    PointXY mapRightBottom() const;
    PointXY mapMinOffset() const;
    PointXY mapMaxOffset() const;
    QSize layerSize() const;

    PointXY computeViewToMap(const PointXY& p) const;
    PointXY computeMapToView(const PointXY& p) const;

    void update();
    virtual void render(QPainter* painter);
    virtual QString type() const = 0;

protected:
    virtual void updateLayer() = 0;

protected:
    QString m_Id;
    bool m_AutoDelte;
    MapCanvasItem* m_Map;
    QImage m_Image;
};

static QString createUid()
{
    return QUuid::createUuid().toString();
}

