#ifndef TILE_H
#define TILE_H

#include <QObject>
#include <QPixmap>

using TileID = std::string;


class Tile
{
public:
    explicit Tile(TileID id,QPixmap* Texture, QRect rect);
    explicit Tile();
private:
    TileID mId;
    QPixmap* mTexture;
    QRect mRect;
signals:

};

#endif // TILE_H
