#ifndef EDITOR_HH
#define EDITOR_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <unordered_map>
#include "tile.h"
#include "startmenu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Editor; }
QT_END_NAMESPACE



class Editor : public QMainWindow
{
    Q_OBJECT

public:
    Editor(QWidget *parent = nullptr);
    ~Editor();
    bool LoadTextures(std::string dirpath);

public slots:
    bool init();

private:
    Ui::Editor *ui;
    QGraphicsScene* mapscene;
    std::unordered_map<TileID,Tile*> tileset;
    std::vector<std::vector<Tile*>> tilesInMap;
};
#endif // EDITOR_HH
