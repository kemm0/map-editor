#include "startmenu.h"
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
    accept();
    close();
}

void StartMenu::on_CancelButton_clicked()
{
    reject();
    close();
}
