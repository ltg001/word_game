/**
 * @file the implementation of login window
 * @author Shell Zhang
 */

#include "login_window.h"
#include "player.h"
#include "register_window.h"
#include "setter.h"
#include "sql_ops.h"
#include "ui_login_window.h"

extern sql_ops *database;   /**< a pointer to the database object */
extern Player * player_ins; /**< a pinter to global Player object */
extern Setter * setter_ins; /**< a pinter to global Setter object */

/**
 * @brief login_window::login_window
 * @param parent
 * @note automatically load img at one spceific position
 */
login_window::login_window( QWidget *parent )
    : QDialog( parent )
    , ui( new Ui::login_window ) {
    ui->setupUi( this );
    ui->pwd_lineEdit->setEchoMode( QLineEdit::Password );

    QImage *img = new QImage;
    if ( !img->load( "YOUR_PATH_HERE" ) ) {
        delete img;
        return;
    }
    ui->label->setPixmap( QPixmap::fromImage( *img ) );
}

login_window::~login_window() { delete ui; }

/**
 * @brief login_window::on_OKBtn_clicked
 * check whether the username and pwd match
 */
void login_window::on_OKBtn_clicked() {
    QString username = ui->username_lineEdit->text();
    QString pwd      = ui->pwd_lineEdit->text();
    qDebug() << "[get input] " << username << " " << pwd;
    if ( database->login( username, pwd ) ) {
        qDebug() << "[logged in] " << username;
        if ( database->get_type( username, pwd ) == 0 ) {
            player_ins = database->login_player( username, pwd );
            player_ins->update();
            accept();
            return;
        } else if ( database->get_type( username, pwd ) == 1 ) {
            setter_ins = database->login_setter( username, pwd );
            setter_ins->update();
            accept();
            return;
        } else if ( database->get_type( username, pwd ) == -1 ) {
            QMessageBox::warning( this, "login failed", "login failed" );
            ui->pwd_lineEdit->clear();
            ui->pwd_lineEdit->setFocus();
            return;
        }
    }
    // QMessageBox::warning(this, "login failed", "login failed");
    ui->pwd_lineEdit->clear();
    ui->pwd_lineEdit->setFocus();
}

/**
 * @brief on_register_2_clicked
 * show the register window
 */
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

/**
 * @brief on_forget_pwd_clicked
 * show the forget_pwd window
 */
void login_window::on_forget_pwd_clicked() {
    reset_pwd *reset = new reset_pwd;
    if ( reset->exec() == QDialog::Accepted ) {
    }
    delete reset;
}
