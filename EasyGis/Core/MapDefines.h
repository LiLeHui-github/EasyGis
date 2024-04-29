#pragma once

#include <QSharedPointer>
#include <QImage>

struct MapConfig
{
    // ��ͼ�㼶
    int ZoomLevel;

    // ��Ƭ����/��������
    int TileCount;

    // ��ͼ���(����)
    double ViewWidth;

    // ��ͼ�ֱ���(m/ÿ����)
    double MapResolution;

    // ������Ƭ���(m)
    double TileUnitWidth;
};


struct TileRequest
{
    double px;
    double py;
    QString url;
};

using TileRequests = QVector<TileRequest>;

struct TileResponse
{
    double px;
    double py;
    QImage image;
};

using TileResponsePtr = QSharedPointer<TileResponse>;

