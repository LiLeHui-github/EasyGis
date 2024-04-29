#include "TileLoaderService.h"

#include <QFile>
#include <QPainter>
#include <QThreadPool>

#include "MapCanvas/MapCanvasItem.h"

TileLoaderService* TileLoaderService::instance()
{
    static TileLoaderService instance;
    return &instance;
}

void TileLoaderService::execute(const TileRequests& requests, const QSize& layerSize, MapCanvasItem* map)
{
    m_Map = map;
    m_Context = QImage{ layerSize, QImage::Format_ARGB32_Premultiplied };

    int count = requests.size();
    for(int i = 0; i < count; ++i)
    {
        ServiceRunable* task = new ServiceRunable(&requests.at(i), this);
        QThreadPool::globalInstance()->start(task);
    }

    QThreadPool::globalInstance()->waitForDone();
}

void TileLoaderService::tileRespose(const TileResponsePtr& response)
{
    QMutexLocker locker(&m_Mutex);

    QPointF pos = m_Map->computeMapToView(PointXY{ response->px, response->py }).toPointF();
    QPainter painter(&m_Context);
    painter.drawImage(pos, response->image);
    painter.end();
}

const QImage& TileLoaderService::getContext() const
{
    return m_Context;
}

TileCache* TileCache::instance()
{
    return m_Instance;
}

TileResponsePtr TileCache::findCache(const TileRequest* request)
{
    QMutexLocker locker(&m_Mutex);

    if (innerBlackList(request))
    {
        return nullptr;
    }

    auto it = m_Cache.find(request->url);
    if(it == m_Cache.end())
    {
        if(!QFile::exists(request->url))
        {
            saveBlackList(request);
            return nullptr;
        }

        TileResponsePtr ptr = TileResponsePtr::create();
        ptr->px = request->px;
        ptr->py = request->py;
        ptr->image = QImage(request->url);

        if(m_Cache.count() > 500)
            m_Cache.clear();
        m_Cache.insert(request->url, ptr);
        return ptr;
    }

    return it.value();
}

void TileCache::saveBlackList(const TileRequest* request)
{
    if (m_BlackList.count() > 500)
        m_BlackList.clear();
    m_BlackList.insert(request->url);
}

bool TileCache::innerBlackList(const TileRequest* request)
{
    auto it = m_BlackList.find(request->url);
    return it != m_BlackList.end();
}

TileCache* TileCache::m_Instance = new TileCache();

ServiceRunable::ServiceRunable(const TileRequest* request, TileLoaderService* service)
    : m_Request(request)
    , m_Service(service)
{
}

void ServiceRunable::run()
{
    TileResponsePtr response = TileCache::instance()->findCache(m_Request);
    if (response.isNull())
        return;
    m_Service->tileRespose(response);
}
