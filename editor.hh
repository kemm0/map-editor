#ifndef EDITOR_HH
#define EDITOR_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <unordered_map>
#include <QKeyEvent>
#include <QListWidgetItem>
#include "tile.hh"
#include "startmenu.hh"
#include "mapscene.hh"
#include "objectlistitem.hh"

QT_BEGIN_NAMESPACE
namespace Ui { class Editor; }
QT_END_NAMESPACE

enum EditState{
    ADD_TILE,
    ADD_OBJECT,
    EDIT_ITEM,
    ERASE_ITEM,
};


class Editor : public QMainWindow
{
    Q_OBJECT

public:
    Editor(QWidget *parent = nullptr);
    ~Editor();
    bool LoadListItems(QListWidget* list);
    void keyPressEvent(QKeyEvent * event) override;
    void showEvent(QShowEvent* event) override;

public slots:
    bool init(int mapWidth, int mapHeight, int tileWidth, int tileHeight);
    void sceneClickAction(QPointF position);

private slots:

    void on_saveFileButton_clicked();

    void on_openObjectFiles_clicked();

    void on_openTileFiles_clicked();

    void on_tileList_itemClicked(QListWidgetItem *item);

    void on_objectList_itemClicked(QListWidgetItem *item);

    void on_EraserToolButton_clicked();

    void on_PenToolButton_clicked();

private:
    Ui::Editor *ui;
    MapScene* mapscene;
    std::unordered_map<TileType,Tile*> tileset;
    std::vector<std::vector<Tile*>> tilesInMap;
    int mMapWidth;
    int mMapHeight;
    int mTileWidth;
    int mTileHeight;
    ObjectListItem* selectedListItem;
    EditState mState;
};
#endif // EDITOR_HH
