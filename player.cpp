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
    last_failed = "";
}

Player::~Player() { delete ui; }

void Player::on_game_clicked() {
    // int current_level = 1;
    //    bonus            = 2;
    //    QString question = database->get_question( level );

    //    if ( question == "-1" ) {
    //        QMessageBox::warning( this, "no question",
    //                              "there is no question for this level" );
    //        return;
    //    }

    //    game G;
    //    G.start_game( question, get_level( question ), this );
    //    if ( G.exec() == QDialog::Accepted ) {
    //        qDebug() << "[bonus] " << bonus;
    //        check_levelup( get_level( question ) );
    //        database->save_person( username, pwd, level, exp, count, nickname
    //        ); update();
    //    }

    bonus = 10;
    if ( play_game() ) {
        qDebug() << "[bonus] " << bonus;
        check_levelup( level );
        database->save_person( username, pwd, level, exp, count, nickname );
        update();
    } else
        QMessageBox::warning( this, "game failed", "game failed" );
}

bool Player::play_game() {
    for ( int i = 0; i < level; i++ ) {
        game G;
        if ( last_failed == "" ) {
            QString question = database->get_question( level );
            qDebug() << "[get question]" << question;
            if ( question == "-1" ) {
                QMessageBox::warning( this, "no question",
                                      "there is no question for this level" );
                return false;
            } else {
                last_failed = question;
                G.start_game( question, get_level( question ), this );
            }
        } else {
            qDebug() << "[last failed] " << last_failed;
            G.start_game( last_failed, get_level( last_failed ), this );
        }
        if ( G.exec() == QDialog::Accepted )
            last_failed = "";
        else
            return false;
    }
    return true;
}

void Player::add_avatar( QString path ) {
    QPixmap *pixmap = new QPixmap( path );
    pixmap->scaled( ui->avatar->size(), Qt::KeepAspectRatio );
    ui->avatar->setScaledContents( true );
    ui->avatar->setPixmap( *pixmap );
}

void Player::update() {
    ui->nickname_edit->setText( this->nickname );
    ui->exp_edit->setText( QString::number( this->exp ) );
    ui->level_edit->setText( QString::number( this->level ) );
    ui->username_edit->setText( this->username );
    ui->count->setText( QString::number( this->count ) );

    QString avatar_path = database->get_avatar( this->username );
    qDebug() << "[avatar_path]" << avatar_path << "[username]"
             << this->username;
    if ( avatar_path != "" ) {
        add_avatar( avatar_path );
    }
}

void Player::get_bonus() {
    if ( bonus == 0 )
        return;
    else
        bonus--;
}

void Player::check_levelup( int temp_level ) {
    exp += bonus;
    exp += temp_level;
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

void Player::on_pushButton_clicked() {
    QFileDialog *fileDialog = new QFileDialog( this );
    fileDialog->setWindowTitle( tr( "open Image" ) );
    fileDialog->setDirectory( "." );
    fileDialog->setNameFilter( tr( "Images(*.png *.jpg *.jpeg *.bmp)" ) );
    fileDialog->setFileMode( QFileDialog::ExistingFiles );
    fileDialog->setViewMode( QFileDialog::Detail );
    QStringList fileNames;
    if ( fileDialog->exec() ) {
        fileNames = fileDialog->selectedFiles();
    }
    if ( fileNames.empty() ) return;
    qDebug() << fileNames;
    add_avatar( fileNames.front() );
    database->save_avatar( username, fileNames.front() );
    update();
}
