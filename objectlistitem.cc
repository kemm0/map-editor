#include "objectlistitem.hh"



ObjectListItem::ObjectListItem(QString name, QPixmap image, QListWidget *parent)
    :QListWidgetItem(QIcon(image),name,parent)
{
    mPixmap = image;
}

ObjectListItem::ObjectListItem(QListWidget *parent)
    :QListWidgetItem(parent)
{

}

QPixmap ObjectListItem::getPixmap()
{
    return mPixmap;
}

ObjectType ObjectListItem::getType()
{
    return mType;
}
