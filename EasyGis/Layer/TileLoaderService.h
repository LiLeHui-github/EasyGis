#pragma once

#include <QVector>
#include <QSet>
#include <QMap>
#include <QObject>
#include <QRunnable>
#include <QMutex>

#include "Core/MapDefines.h"

class MapCanvasItem;

class TileLoaderService : public QObject
{
    Q_OBJECT
public:
    static TileLoaderService* instance();

    void execute(const TileRequests& requests, const QSize& layerSize, MapCanvasItem* map);
    void tileRespose(const TileResponsePtr& response);

    const QImage& getContext() const;

private:
    MapCanvasItem* m_Map = nullptr;
    QMutex m_Mutex;
    QImage m_Context;
};

class TileCache
{
public:
    static TileCache* instance();

    TileResponsePtr findCache(const TileRequest* request);

private:
    void saveBlackList(const TileRequest* request);
    bool innerBlackList(const TileRequest* request);

private:
    static TileCache* m_Instance;
    QMutex m_Mutex;
    QSet<QString> m_BlackList;
    QMap<QString, TileResponsePtr> m_Cache;
};

class ServiceRunable : public QRunnable
{
public:
    ServiceRunable(const TileRequest* request, TileLoaderService* service);
    void run() override;
private:
    const TileRequest* m_Request;
    TileLoaderService* m_Service;
};
