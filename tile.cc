#include "tile.hh"

Tile::Tile(TileType type, QPixmap& texture, QPoint pos, int zValue, QGraphicsItem* parent)
    :QGraphicsPixmapItem(parent)
{
    mType = type;
    setPixmap(texture);
    setPos(pos);
}

TileType Tile::getType()
{
    return mType;
}

int Tile::getZValue()
{
    return zValue();
}
