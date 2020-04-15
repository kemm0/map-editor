#include "editor.hh"
#include "ui_editor.h"
#include <QGraphicsRectItem>
#include <iostream>
#include <QFileInfo>
#include <QFileDialog>
#include <QStringList>
#include <fstream>
#include <QDebug>


Editor::Editor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Editor)
{
    ui->setupUi(this);
    mapscene = new MapScene(ui->graphicsView);
    ui->graphicsView->setScene(mapscene);
    ui->graphicsView->setSceneRect(mapscene->sceneRect());
    ui->graphicsView->show();
    //mapscene->addRect(QRectF(-10,-10,20,20));
    ui->tileList->setIconSize(QSize(64,64));
    ui->objectList->setIconSize(QSize(64,64));
    ui->tileList->addItem(QString("none"));
    QObject::connect(mapscene,&MapScene::mouseClicked,this,&Editor::sceneClickAction);
    ui->PenToolButton->setIcon(QIcon("resources/icons/pen.png"));
    ui->EraserToolButton->setIcon(QIcon("resources/icons/eraser.png"));
    ui->FillToolButton->setIcon(QIcon("resources/icons/bucket.png"));
}

Editor::~Editor()
{
    delete ui;
    delete mapscene;
}

bool Editor::LoadListItems(QListWidget* list)
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this);
    for(auto filename : fileNames){
        QFileInfo fileinfo = QFileInfo(filename);
        QString itemName = fileinfo.fileName();
        list->addItem(new ObjectListItem(itemName,QPixmap(filename)));
    }
}

void Editor::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Minus){
        ui->graphicsView->scale(0.9,0.9);
    }
    else if(event->key() == Qt::Key_Plus){
        ui->graphicsView->scale(1.1,1.1);
    }
}

void Editor::showEvent(QShowEvent *event)
{
    ui->graphicsView->fitInView(mapscene->sceneRect());
}

bool Editor::init(int mapWidth, int mapHeight, int tileWidth, int tileHeight)
{
    mMapWidth = mapWidth;
    mMapHeight = mapHeight;
    mTileWidth = tileWidth;
    mTileHeight = tileHeight;

    for(int i = 0;i < mMapHeight; i++){
        for(int j = 0; j < mMapWidth;j++){
            QGraphicsRectItem* tile = new QGraphicsRectItem(0,0,mTileWidth,mTileHeight);
            tile->setZValue(0);
            //tile->setBrush(QBrush(Qt::blue));
            tile->setPos(j*tileWidth,i*tileHeight);
            tile->setVisible(true);
            mapscene->addItem(tile);
        }
    }
    return true;
}

void Editor::sceneClickAction(QPointF position)
{
    bool outOfBounds = (position.x() > mTileWidth*mMapWidth
                        || position.y() > mTileHeight*mMapHeight
                        || position.x() < 0
                        || position.y() < 0);

    if(mState == EditState::ADD_TILE && !outOfBounds){
        int x = int(position.x()/mTileWidth)*mTileWidth;
        int y = int(position.y()/mTileHeight)*mTileHeight;
        std::cout<<x<<" "<<y<<std::endl;
        QPixmap texture = selectedListItem->getPixmap();
        Tile* tile = new Tile(selectedListItem->text().toStdString(),texture,QPoint(x,y),2);
        tile->setZValue(2);
        mapscene->addTile(tile);
    }
    else if(mState == EditState::ADD_OBJECT && !outOfBounds){
        int x = position.x()-selectedListItem->getPixmap().size().width()/2;
        int y = position.y()-selectedListItem->getPixmap().size().height()/2;
        std::cout<<x<<" "<<y<<std::endl;
        QPixmap texture = selectedListItem->getPixmap();
        Tile* tile = new Tile(selectedListItem->text().toStdString(),texture,QPoint(x,y),3);
        tile->setZValue(3);
        mapscene->addTile(tile);
    }
    else if(mState == EditState::ERASE_ITEM){
        mapscene->removeItem(mapscene->itemAt(position,QTransform()));
    }
}

void Editor::on_saveFileButton_clicked()
{
    QString saveFileUrl = QFileDialog::getSaveFileUrl(
                this).toString();
    saveFileUrl.remove(0,8);
    //saveFileUrl.replace("/","'\'");
    qDebug()<<saveFileUrl;

    std::ofstream writeFile(saveFileUrl.toStdString());
    for(auto tile : mapscene->getTiles()){
        writeFile<<tile->getType()<<" "<<tile->scenePos().x()/mTileWidth<<" "<<int(tile->scenePos().y())/mTileHeight<<" "<<tile->getZValue()<<std::endl;
    }
    writeFile.close();
}

void Editor::on_openObjectFiles_clicked()
{
    LoadListItems(ui->objectList);
    mState = EditState::ADD_OBJECT;
}

void Editor::on_openTileFiles_clicked()
{
    LoadListItems(ui->tileList);
    mState = EditState::ADD_TILE;
}

void Editor::on_tileList_itemClicked(QListWidgetItem *item)
{
    if(item->text() == QString("none")){
        selectedListItem = nullptr;
    }
    else{
        selectedListItem = dynamic_cast<ObjectListItem*>(item);
    }
}

void Editor::on_objectList_itemClicked(QListWidgetItem *item)
{
    selectedListItem = dynamic_cast<ObjectListItem*>(item);
}

void Editor::on_EraserToolButton_clicked()
{
    mState = EditState::ERASE_ITEM;
}

void Editor::on_PenToolButton_clicked()
{
    if(selectedListItem->getType() == ObjectType::TILE){
        mState = EditState::ADD_TILE;
    }
    else if(selectedListItem->getType() == ObjectType::OBJECT){
        mState = EditState::ADD_OBJECT;
    }
}
