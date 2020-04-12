#include "mapscene.h"
#include <iostream>
#include <QGraphicsItem>
#include <QGraphicsColorizeEffect>


MapScene::MapScene(QObject *parent)
    : QGraphicsScene(parent)
{

}

MapScene::~MapScene()
{

}

void MapScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    for(auto item : items()){
        if(item->graphicsEffect() != nullptr){
            delete item->graphicsEffect();
            item->setGraphicsEffect(nullptr);
        }
    }
    QGraphicsItem* item = itemAt(event->scenePos(),QTransform());
    highlight(item);
    emit mouseClicked(int(item->scenePos().x()),int(item->scenePos().y()));
    //std::cout<<item->scenePos().x()<<" "<<item->scenePos().y()<<std::endl;
}

void MapScene::highlight(QGraphicsItem* item)
{
    if(item != nullptr){
        QGraphicsColorizeEffect* graphicsEffect = new QGraphicsColorizeEffect;
        graphicsEffect->setColor(QColor(Qt::white));
        graphicsEffect->setStrength(0.1);
        item->setGraphicsEffect(graphicsEffect);
    }
}

