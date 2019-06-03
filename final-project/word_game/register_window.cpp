#include "register_window.h"
#include "ui_register_window.h"

#include "sql_ops.h"
extern sql_ops *database;

register_window::register_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::register_window)
{
    ui->setupUi(this);
    ui->pwdEdit->setEchoMode(QLineEdit::Password);
    ui->player->setChecked(true);
}

register_window::~register_window()
{
    delete ui;
}

void register_window::on_OKBtn_clicked() {
    QString username = ui->usernameEdit->text();
    QString pwd = ui->pwdEdit->text();
    int type = -1;
    if(ui->player->isChecked()) {
        type = 0;
        database->user_register(username, pwd, type);
        accept();
        return;
    }
    if(ui->setter->isChecked()) {
        type = 1;
        database->user_register(username, pwd, type);
        accept();
        return;
    }
    if(type == -1)
        QMessageBox::warning(this, "wrong input", "select one role to register");
    return;
}
