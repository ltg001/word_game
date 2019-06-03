#include "view_all_question.h"
#include "client.h"
#include "ui_view_all_question.h"

extern client *client_sender;

extern QQueue<QString>             question_item;
extern QQueue<QPair<int, QString>> player_rank;
extern QQueue<QPair<int, QString>> setter_rank;
extern bool                        locked;
extern QQueue<int>                 msg_queue;

View_all_question::View_all_question( QWidget *parent )
    : QDialog( parent )
    , ui( new Ui::View_all_question ) {
    ui->setupUi( this );
    auto item = ui->listWidget;
    // database->load_question_item( item );

    //    QQueue<QPair<int, QString>> *ranks = database->get_rank();
    //    if ( ranks->empty() )
    //        QMessageBox::critical( this, "List empty", "No available players."
    //        );
    //    else {
    //        int i = 1;
    //        while ( !ranks->empty() ) {
    //            ui->ranks->addItem( new QListWidgetItem(
    //                QString( "rank: %1, username: %2, number of questions: %3"
    //                )
    //                    .arg( i )
    //                    .arg( ranks->front().second )
    //                    .arg( ranks->front().first ) ) );
    //            ranks->pop_front();
    //        }
    //    }

    // database->get_rank( ui->ranks, ui->setter );

    locked = true;
    QJsonArray array;
    client_sender->construct_json( "load_question_item", array );
    while ( locked ) {
        QTime dieTime = QTime::currentTime().addMSecs( 100 );
        while ( QTime::currentTime() < dieTime )
            QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
    if ( msg_queue.front() == 1 ) {
        while ( !question_item.empty() ) {
            item->addItem( new QListWidgetItem( question_item.front() ) );
            question_item.pop_front();
        }
    } else {
        QMessageBox::warning( this, "error", "can't load questions" );
    }
    msg_queue.pop_front();

    locked = true;
    client_sender->construct_json( "load_player_rank", array );
    while ( locked ) {
        QTime dieTime = QTime::currentTime().addMSecs( 100 );
        while ( QTime::currentTime() < dieTime )
            QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
    if ( msg_queue.front() == 1 ) {
        int i = 0;
        while ( !player_rank.empty() ) {
            ui->ranks->addItem( new QListWidgetItem(
                QString( "rank: %1, username: %2, count: %3" )
                    .arg( i + 1 )
                    .arg( player_rank.front().second )
                    .arg( player_rank.front().first ) ) );
            qDebug() << player_rank;
            player_rank.pop_front();
        }
    } else {
        QMessageBox::warning( this, "error", "can't load player rank" );
    }
    msg_queue.pop_front();

    locked = true;
    client_sender->construct_json( "load_setter_rank", array );
    while ( locked ) {
        QTime dieTime = QTime::currentTime().addMSecs( 100 );
        while ( QTime::currentTime() < dieTime )
            QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
    if ( msg_queue.front() == 1 ) {
        int i = 0;
        while ( !setter_rank.empty() ) {
            ui->setter->addItem( new QListWidgetItem(
                QString( "rank: %1, username: %2, count: %3" )
                    .arg( ++i )
                    .arg( setter_rank.front().second )
                    .arg( setter_rank.front().first ) ) );
            qDebug() << setter_rank;
            setter_rank.pop_front();
        }
    } else {
        QMessageBox::warning( this, "error", "can't load setter rank" );
    }
    msg_queue.pop_back();
}

View_all_question::~View_all_question() { delete ui; }
