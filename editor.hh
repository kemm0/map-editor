#ifndef EDITOR_HH
#define EDITOR_HH

#include <QMainWindow>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class Editor; }
QT_END_NAMESPACE

class Editor : public QMainWindow
{
    Q_OBJECT

public:
    Editor(QWidget *parent = nullptr);
    ~Editor();

private:
    Ui::Editor *ui;
    QGraphicsScene* mapscene;
};
#endif // EDITOR_HH
