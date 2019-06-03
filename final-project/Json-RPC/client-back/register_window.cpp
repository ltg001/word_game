#include "register_window.h"
#include "client.h"
#include "ui_register_window.h"

extern bool        locked;
extern QQueue<int> msg_queue;

extern client *client_sender;

register_window::register_window( QWidget *parent )
    : QDialog( parent )
    , ui( new Ui::register_window ) {
    ui->setupUi( this );
    ui->pwdEdit->setEchoMode( QLineEdit::Password );
    ui->player->setChecked( true );
}

register_window::~register_window() { delete ui; }

void register_window::on_OKBtn_clicked() {
    QString username = ui->usernameEdit->text();
    QString pwd      = ui->pwdEdit->text();
    int     type     = -1;
    if ( ui->player->isChecked() ) {
        type = 0;
        // database->user_register( username, pwd, type );

        QJsonArray array;
        array.push_back( username );
        array.push_back( pwd );
        array.push_back( QString( "%1" ).arg( type ) );
        client_sender->construct_json( "user_register", array );
        locked = true;
        qDebug() << "locked at on_OKBtn_clicked in register_window";
        while ( locked ) { // wait for response
            QTime dieTime = QTime::currentTime().addMSecs( 100 );
            while ( QTime::currentTime() < dieTime )
                QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
        }
        if ( msg_queue.front() == 1 ) {
            msg_queue.pop_front();
            accept();
            return;
        } else {
            QMessageBox::warning( this, "register error", "database error" );
            ui->pwdEdit->clear();
            ui->pwdEdit->setFocus();
        }
    }
    if ( ui->setter->isChecked() ) {
        type = 1;
        QJsonArray array;
        array.push_back( username );
        array.push_back( pwd );
        array.push_back( QString( "%1" ).arg( type ) );
        client_sender->construct_json( "user_register", array );
        locked = true;
        while ( locked ) { // wait for response
            QTime dieTime = QTime::currentTime().addMSecs( 100 );
            while ( QTime::currentTime() < dieTime )
                QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
        }
        if ( msg_queue.front() == 1 ) {
            msg_queue.pop_front();
            accept();
            return;
        } else {
            QMessageBox::warning( this, "register error", "database error" );
            ui->pwdEdit->clear();
            ui->pwdEdit->setFocus();
        }
    }
    if ( type == -1 )
        QMessageBox::warning( this, "wrong input",
                              "select one role to register" );
    return;
}
