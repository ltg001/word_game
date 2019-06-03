#include "login_window.h"
#include "client.h"
#include "player.h"
#include "register_window.h"
#include "setter.h"
#include "ui_login_window.h"

extern Player *    player_ins;
extern Setter *    setter_ins;
extern bool        locked;
extern QQueue<int> msg_queue;

extern client *client_sender;

login_window::login_window( QWidget *parent )
    : QDialog( parent )
    , ui( new Ui::login_window ) {
    ui->setupUi( this );
    ui->pwd_lineEdit->setEchoMode( QLineEdit::Password );

    QImage *img = new QImage;
    if ( !img->load(
             "C:\\Users\\Tabulator\\Desktop\\c++_oop\\final-project\\word_"
             "game\\resource\\index.png" ) ) {
        delete img;
        return;
    }
    ui->label->setPixmap( QPixmap::fromImage( *img ) );
}

login_window::~login_window() { delete ui; }

void login_window::on_OKBtn_clicked() {
    QString username = ui->username_lineEdit->text();
    QString pwd      = ui->pwd_lineEdit->text();
    qDebug() << "[get input] " << username << " " << pwd;
    //    if ( database->login( username, pwd ) ) {
    //        qDebug() << "[logged in] " << username;
    //        if ( database->get_type( username, pwd ) == 0 ) {
    //            player_ins = database->login_player( username, pwd );
    //            player_ins->update();
    //            accept();
    //            return;
    //        } else if ( database->get_type( username, pwd ) == 1 ) {
    //            setter_ins = database->login_setter( username, pwd );
    //            setter_ins->update();
    //            accept();
    //            return;
    //        } else if ( database->get_type( username, pwd ) == -1 ) {
    //            QMessageBox::warning( this, "login failed", "login failed" );
    //            ui->pwd_lineEdit->clear();
    //            ui->pwd_lineEdit->setFocus();
    //            return;
    //        }
    //    }
    // QMessageBox::warning(this, "login failed", "login failed");

    locked = true;
    qDebug() << "locked at on_OKBtn_clicked";
    QJsonArray array;
    array.push_back( username );
    array.push_back( pwd );
    client_sender->construct_json( "login", array );

    while ( locked ) { // wait for response
        QTime dieTime = QTime::currentTime().addMSecs( 100 );
        while ( QTime::currentTime() < dieTime )
            QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }

    if ( msg_queue.front() == 1 ) {
        qDebug() << "[client login] success";
        msg_queue.pop_front();
        accept();
        return;
    } else {
        QMessageBox::warning( this, "login failed",
                              "wrong username or password" );
    }
    msg_queue.pop_front();

    ui->pwd_lineEdit->clear();
    ui->pwd_lineEdit->setFocus();
}

void login_window::on_register_2_clicked() {
    register_window re;
    if ( re.exec() == QDialog::Accepted ) {
        return;
    } else {
        QMessageBox::warning( this, "Register error", "Register failed" );
        return;
    }
}

#include "reset_pwd.h"

void login_window::on_forget_pwd_clicked() {
    reset_pwd *reset = new reset_pwd;
    if ( reset->exec() == QDialog::Accepted ) {
    }
    delete reset;
}
