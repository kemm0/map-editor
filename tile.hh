#ifndef TILE_H
#define TILE_H

#include <QObject>
#include <QPixmap>
#include <QGraphicsPixmapItem>

using TileType = std::string;


class Tile : public QGraphicsPixmapItem
{

public:
    explicit Tile(TileType type,QPixmap& Texture, QPoint pos,int zValue, QGraphicsItem * parent = nullptr);
    explicit Tile();
    TileType getType();
    int getZValue();
private:
    TileType mType;
    int mZValue;
signals:

};

#endif // TILE_H
