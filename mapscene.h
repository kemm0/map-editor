#ifndef MAPSCENE_H
#define MAPSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "tile.h"

class MapScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MapScene(QObject *parent = nullptr);
    ~MapScene() override;
    void highlight(QGraphicsItem* tile);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void setPlaceableTile();
    void addTile(Tile* tile);
    std::vector<Tile*> getTiles();
signals:
    void mouseClicked(int x, int y);

private:
    std::vector<Tile*> mTiles;
};

#endif // MAPSCENE_H
