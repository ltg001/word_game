#include "view_all_question.h"
#include "sql_ops.h"
#include "ui_view_all_question.h"

extern sql_ops *database;

View_all_question::View_all_question( QWidget *parent )
    : QDialog( parent )
    , ui( new Ui::View_all_question ) {
    ui->setupUi( this );
    auto item = ui->listWidget;
    database->load_question_item( item );

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

    database->get_rank( ui->ranks, ui->setter );
}

View_all_question::~View_all_question() { delete ui; }
