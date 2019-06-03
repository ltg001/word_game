#include "include.h"
#include "login_window.h"
#include "mainwindow.h"
#include "player.h"
#include "setter.h"
#include "sql_ops.h"
#include "style.h"
#include <QApplication>

#include <QFont>

sql_ops *database;
Player * player_ins;
Setter * setter_ins;

int main( int argc, char *argv[] ) {
    player_ins = nullptr;
    setter_ins = nullptr;

    // style::set_style();
    QApplication a( argc, argv );

    QFont font;
    font.setPointSize( 10 );
    font.setFamily( "Microsoft YaHei" );
    a.setFont( font );

    database            = new sql_ops();
    login_window *login = new login_window();
    if ( login->exec() == QDialog::Accepted ) {
        if ( player_ins ) {
            qDebug() << "start player";
            player_ins->exec();
            // return 0;
        }
        if ( setter_ins ) {
            qDebug() << "start setter";
            setter_ins->exec();
        }
        // if(!player_ins && !setter_ins)
    }
    // QMessageBox::warning(a, "login failed", "wrong username or password");
    return 0;
}
