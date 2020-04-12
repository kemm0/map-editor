#include "editor.hh"
#include "startmenu.hh"

#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Editor w;
    StartMenu sm;
    QObject::connect(&sm,&StartMenu::dataSubmitted,&w,&Editor::init);
    if(sm.exec() == QDialog::Accepted){
        w.show();
        return a.exec();
    }
    else{
        return QDialog::Rejected;
    }
}
