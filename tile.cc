#include "tile.hh"

Tile::Tile()
{

}

Tile::Tile(TileID id, QPixmap* texture, QRect rect)
{
    mId = id;
    mTexture = texture;
    mRect = rect;
}
