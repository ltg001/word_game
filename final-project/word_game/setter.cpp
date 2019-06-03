#include "setter.h"
#include "sql_ops.h"
#include "ui_setter.h"
#include "view_all_question.h"

extern sql_ops *database;

Setter::Setter( QWidget *parent )
    : QDialog( parent )
    , ui( new Ui::Setter ) {
    ui->setupUi( this );
    update();
}

Setter::~Setter() { delete ui; }

void Setter::on_question_clicked() {
    View_all_question v;
    v.exec();
    return;
}

void Setter::on_submit_clicked() {
    QString question = ui->question_edit->text();
    if ( database->add_question( question, get_level( question ), username ) ) {
        QMessageBox::warning( this, "insert successful", "insert successful" );
        count++;
        check_levelup( get_level( question ) );
        ui->question_edit->clear();
    } else {
        QMessageBox::warning( this, "insert failed", "insert failed" );
        qDebug() << "[insert question error]";
        ui->question_edit->clear();
        ui->question_edit->setFocus();
    }
    database->save_person( username, pwd, level, exp, count, nickname );
    update();
}

// int Setter::get_level(QString s) {
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

void Setter::update() {
    ui->username_edit->setText( username );
    ui->nickname_edit->setText( nickname );
    ui->exp_edit->setText( QString::number( exp ) );
    ui->level_edit->setText( QString::number( level ) );
    ui->question_num->setText( QString::number( count ) );

    QString avatar_path = database->get_avatar( this->username );
    qDebug() << "[avatar_path]" << avatar_path << "[username]"
             << this->username;
    if ( avatar_path != "" ) {
        add_avatar( avatar_path );
    }
}

void Setter::on_change_clicked() {
    if ( ui->nickname_2->text() == "" ) return;
    nickname = ui->nickname_2->text();
    ui->nickname_2->clear();
    database->save_person( username, pwd, level, exp, count, nickname );
    update();
}

void Setter::check_levelup( int question_level ) {
    exp += question_level;
    int temp = level;
    level += exp / ( 2 * level + 1 );
    exp %= 2 * temp + 1;
    count += 1;
    qDebug() << "[setter] " << exp;
}

void Setter::add_avatar( QString path ) {
    QPixmap *pixmap = new QPixmap( path );
    pixmap->scaled( ui->avatar->size(), Qt::KeepAspectRatio );
    ui->avatar->setScaledContents( true );
    ui->avatar->setPixmap( *pixmap );
}

void Setter::on_change_avatar_clicked() {
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
