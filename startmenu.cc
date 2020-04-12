#include "startmenu.hh"
#include "ui_startmenu.h"

StartMenu::StartMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartMenu)
{
    ui->setupUi(this);
}

StartMenu::~StartMenu()
{
    delete ui;
}

void StartMenu::on_CreateButton_clicked()
{
    int mapWidth = std::stoi(ui->MapWidth->text().toStdString());
    int mapHeight = std::stoi(ui->MapHeight->text().toStdString());
    int tileWidth = std::stoi(ui->TileWidth->text().toStdString());
    int tileHeight = std::stoi(ui->TileHeight->text().toStdString());
    emit dataSubmitted(mapWidth,mapHeight,tileWidth,tileHeight);
    accept();
    close();
}

void StartMenu::on_CancelButton_clicked()
{
    reject();
    close();
}
