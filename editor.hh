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

QT_BEGIN_NAMESPACE
namespace Ui { class Editor; }
QT_END_NAMESPACE

enum EditState{
    ADD_ITEM,
    EDIT_ITEM,
    REMOVE_ITEM,
};

class Editor : public QMainWindow
{
    Q_OBJECT

public:
    Editor(QWidget *parent = nullptr);
    ~Editor();
    bool LoadTextures(std::string dirpath);
    void keyPressEvent(QKeyEvent * event) override;

public slots:
    bool init(int mapWidth, int mapHeight, int tileWidth, int tileHeight);
    void sceneClickAction(int x, int y);

private slots:
    void on_openSpriteFiles_clicked();

    void on_itemList_itemClicked(QListWidgetItem *item);

private:
    Ui::Editor *ui;
    MapScene* mapscene;
    std::unordered_map<TileID,Tile*> tileset;
    std::vector<std::vector<Tile*>> tilesInMap;
    int mMapWidth;
    int mMapHeight;
    int mTileWidth;
    int mTileHeight;
    QListWidgetItem* selectedListItem;
    EditState mState;
};
#endif // EDITOR_HH
