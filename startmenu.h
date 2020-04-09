#ifndef STARTMENU_H
#define STARTMENU_H

#include <QDialog>

namespace Ui {
class StartMenu;
}

class StartMenu : public QDialog
{
    Q_OBJECT

public:
    explicit StartMenu(QWidget *parent = nullptr);
    ~StartMenu();

signals:
    void dataSubmitted(int mapWidth, int mapHeight, int tileWidth, int tileHeight, std::string texturespath);

private slots:
    void on_CreateButton_clicked();

    void on_CancelButton_clicked();




private:
    Ui::StartMenu *ui;
};

#endif // STARTMENU_H
