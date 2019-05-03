#include "player.h"
#include "game.h"
#include "sql_ops.h"
#include "ui_player.h"
#include "view_all_question.h"

extern sql_ops *database;

Player::Player( QWidget *parent )
    : QDialog( parent )
    , ui( new Ui::Player ) {
    ui->setupUi( this );
    update();
    qDebug() << "[test Player]" << this->count << " " << this->username;
}

Player::~Player() { delete ui; }

void Player::on_game_clicked() {
    // int current_level = 1;
    QString question = database->get_question( level );

    if ( question == "-1" ) {
        QMessageBox::warning( this, "no question",
                              "there is no question for this level" );
        return;
    }

    game G;
    G.start_game( question, get_level( question ) );
    if ( G.exec() == QDialog::Accepted ) {
        check_levelup();
        database->save_person( username, pwd, level, exp, count, nickname );
        update();
    }
}

void Player::update() {
    ui->nickname_edit->setText( this->nickname );
    ui->exp_edit->setText( QString::number( this->exp ) );
    ui->level_edit->setText( QString::number( this->level ) );
    ui->username_edit->setText( this->username );
    ui->count->setText( QString::number( this->count ) );
}

void Player::check_levelup() {
    exp += 1;
    int temp = level;
    level += exp / ( 2 * level + 1 );
    exp %= 2 * temp + 1;
    count += 1;
    qDebug() << "[player]" << exp;
}

// int Player::get_level(QString s) {
//    if(s.length() <= 3)
//        return 1;
//    else if(s.length() <= 6)
//        return 2;
//    else if(s.length() <= 9)
//        return 3;
//    else if(s.length() <= 12)
//        return 4;
//    else
//        return 5;
//}

void Player::on_questions_clicked() { // TODO
    View_all_question v;
    v.exec();
    return;
}

void Player::on_change_clicked() {
    if ( ui->change_nickname->text() == "" ) return;
    nickname = ui->change_nickname->text();
    ui->change_nickname->clear();
    database->save_person( username, pwd, level, exp, count, nickname );
    update();
}
