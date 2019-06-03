#include "reset_pwd.h"
#include "client.h"
#include "ui_reset_pwd.h"

extern bool        locked;
extern QQueue<int> msg_queue;

extern client *client_sender;

reset_pwd::reset_pwd( QWidget *parent )
    : QDialog( parent )
    , ui( new Ui::reset_pwd ) {
    ui->setupUi( this );
    ui->new_pwd->setEchoMode( QLineEdit::Password );
}

reset_pwd::~reset_pwd() { delete ui; }

void reset_pwd::on_OKBtn_clicked() {
    QString username = ui->username->text();
    int     level    = ui->level->text().toInt();
    int     exp      = ui->exp->text().toInt();
    int     count    = ui->count->text().toInt();
    QString new_pwd  = ui->new_pwd->text();
    //    if ( !database->reset_pwd( username, level, exp, count, new_pwd ) ) {
    //            QMessageBox::warning( this, "something wrong",
    //                                  "there are some mistakes in your input"
    //                                  );
    //            ui->count->clear();
    //            ui->exp->clear();
    //            ui->username->clear();
    //            ui->new_pwd->clear();
    //            ui->level->clear();
    //    }

    QJsonArray array;
    array.push_back( username );
    array.push_back( QString( "%1" ).arg( level ) );
    array.push_back( QString( "%1" ).arg( exp ) );
    array.push_back( QString( "%1" ).arg( count ) );
    array.push_back( new_pwd );
    locked = true;
    while ( locked ) {
        QTime dieTime = QTime::currentTime().addMSecs( 100 );
        while ( QTime::currentTime() < dieTime )
            QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
    if ( msg_queue.front() == 1 ) {
        accept();
        return;
    } else {
        QMessageBox::warning( this, "something wrong",
                              "there are some mistakes in your input" );
        ui->count->clear();
        ui->exp->clear();
        ui->username->clear();
        ui->new_pwd->clear();
        ui->level->clear();
    }
    msg_queue.pop_front();
}
