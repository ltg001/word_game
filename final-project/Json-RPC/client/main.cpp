#include "mainwindow.h"
#include <QApplication>

#include "client.h"
#include "player.h"
#include "setter.h"

#include "login_window.h"

Player *player_ins = NULL;
Setter *setter_ins = NULL;

QQueue<QPair<int, QString>> player_rank;
QQueue<QPair<int, QString>> setter_rank;
QQueue<QString>             question_item;
QQueue<int>                 msg_queue;
QString                     exec_result;

client *client_sender = NULL;

bool locked = false;

int main( int argc, char *argv[] ) {
    //    QApplication a( argc, argv );
    //    MainWindow   w;
    //    // w.show();
    //    client_sender = new client;
    //    QJsonArray array;
    //    array.append( "qwwwq" );
    //    array.append( "2" );
    //    array.append( "qwe" );
    //    client_sender->construct_json( "add_question", array );
    //    if ( client_sender->exec() == QDialog::Accepted ) {
    //    }

    player_ins = nullptr;
    setter_ins = nullptr;

    // style::set_style();
    QApplication a( argc, argv );

    QFont font;
    font.setPointSize( 10 );
    font.setFamily( "Microsoft YaHei" );
    a.setFont( font );

    client_sender = new client;

    login_window *login = new login_window();
    if ( login->exec() == QDialog::Accepted ) {
        if ( player_ins ) {
            player_ins->update();
            player_ins->load_avatar();
            qDebug() << "start player";
            player_ins->exec();
            // return 0;
        }
        if ( setter_ins ) {
            setter_ins->update();
            setter_ins->load_avatar();
            qDebug() << "start setter";
            setter_ins->exec();
        }
        // if(!player_ins && !setter_ins)
    }
    // QMessageBox::warning(a, "login failed", "wrong username or password");
    return 0;
}
