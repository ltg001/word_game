#include "mainwindow.h"
#include <QApplication>
#include "include.h"
#include "player.h"
#include "setter.h"
#include "login_window.h"
#include "sql_ops.h"

sql_ops *database;
Player *player_ins;
Setter *setter_ins;


int main(int argc, char *argv[])
{
    player_ins = nullptr;
    setter_ins = nullptr;

    QApplication a(argc, argv);
    database = new sql_ops();
    login_window *login = new login_window();
    if(login->exec() == QDialog::Accepted) {
        if(player_ins) {
            qDebug() << "start player";
            player_ins->exec();
            //return 0;
        }
        if(setter_ins) {
            qDebug() << "start setter";
            setter_ins->exec();
        }
        //if(!player_ins && !setter_ins)
    }
    //QMessageBox::warning(a, "login failed", "wrong username or password");
    return 0;
}
