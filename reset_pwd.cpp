#include "reset_pwd.h"
#include "sql_ops.h"
#include "ui_reset_pwd.h"

extern sql_ops *database;

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
    if ( !database->reset_pwd( username, level, exp, count, new_pwd ) ) {
        QMessageBox::warning( this, "something wrong",
                              "there are some mistakes in your input" );
        ui->count->clear();
        ui->exp->clear();
        ui->username->clear();
        ui->new_pwd->clear();
        ui->level->clear();
    }
}
