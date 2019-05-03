#include "include.h"
#include "ui_game.h"
#include "game.h"

game::game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::game)
{
    QString s = "";
    ui->setupUi(this);
}

game::~game()
{
    delete ui;
}

void game::set_text(const QString _s) {
    ui->question->setText(_s);
}

void game::cancel_context() {
    ui->question->setText("");
}

void game::start_game(const QString _s, int level) {
    this->set_text(_s);
    QTimer::singleShot(1000 * (6 - level), this, SLOT(cancel_context()));
    s = _s;
}

void game::on_cancelBtn_clicked()
{
    close();
}

void game::on_OKBtn_clicked()
{
    if(ui->answer->text() == s)
        accept();
    else
        close();
}
