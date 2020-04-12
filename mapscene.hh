#ifndef MAPSCENE_H
#define MAPSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class MapScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MapScene(QObject *parent = nullptr);
    ~MapScene() override;
    void highlight(QGraphicsItem* tile);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void setPlaceableTile();
signals:
    void mouseClicked(int x, int y);
};

#endif // MAPSCENE_H
