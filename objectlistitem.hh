#ifndef OBJECTLISTITEM_HH
#define OBJECTLISTITEM_HH
#include <QListWidgetItem>

enum ObjectType{
    OBJECT,
    TILE
};

class ObjectListItem : public QListWidgetItem
{
public:
    ObjectListItem(QString name, QPixmap image, QListWidget* parent = nullptr);
    ObjectListItem(QListWidget* parent = nullptr);
    QPixmap getPixmap();
    ObjectType getType();
private:
    QPixmap mPixmap;
    ObjectType mType;
};

#endif // OBJECTLISTITEM_HH
