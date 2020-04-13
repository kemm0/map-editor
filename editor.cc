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
    ui->itemList->setIconSize(QSize(64,64));
    ui->itemList->addItem(QString("none"));
    QObject::connect(mapscene,&MapScene::mouseClicked,this,&Editor::sceneClickAction);
}

Editor::~Editor()
{
    delete ui;
    delete mapscene;
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

void Editor::sceneClickAction(int x, int y)
{
    std::cout<<x<<" "<<y<<std::endl;
    if(mState == EditState::ADD_ITEM){
        QPixmap texture = selectedListItem->icon().pixmap(QSize(mTileWidth,mTileHeight));
        Tile* tile = new Tile(selectedListItem->text().toStdString(),texture,QPoint(x,y),1);
        tile->setZValue(1);
        mapscene->addTile(tile);
    }
}


void Editor::on_openSpriteFiles_clicked()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this);
    for(auto filename : fileNames){
        QFileInfo fileinfo = QFileInfo(filename);
        QString itemName = fileinfo.fileName();
        itemName.chop(4);
        ui->itemList->addItem(new QListWidgetItem(QIcon(QPixmap(filename)),itemName));
    }
}

void Editor::on_itemList_itemClicked(QListWidgetItem *item)
{
    if(item->text() == QString("none")){
        selectedListItem = nullptr;
    }
    else{
        selectedListItem = item;
        mState = EditState::ADD_ITEM;
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
