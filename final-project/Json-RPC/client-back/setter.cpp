#include "setter.h"
#include "client.h"
#include "ui_setter.h"
#include "view_all_question.h"

extern client *    client_sender;
extern bool        locked;
extern QQueue<int> msg_queue;
extern QString     exec_result;

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

    QJsonArray array;
    array.append( question );
    array.append( QString( "%1" ).arg( get_level( question ) ) );
    array.append( username );
    locked = true;
    client_sender->construct_json( "add_question", array );
    while ( locked ) {
        QTime dieTime = QTime::currentTime().addMSecs( 100 );
        while ( QTime::currentTime() < dieTime )
            QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }

    // if ( database->add_question( question, get_level( question ), username )
    // ) {
    if ( msg_queue.front() == 1 ) {
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
    msg_queue.pop_front();
    // database->save_person( username, pwd, level, exp, count, nickname );
    while ( !array.isEmpty() ) {
        array.pop_front();
    }
    array.append( username );
    array.append( pwd );
    array.append( QString( "%1" ).arg( level ) );
    array.append( QString( "%1" ).arg( exp ) );
    array.append( QString( "%1" ).arg( count ) );
    array.append( nickname );
    client_sender->construct_json( "save_person", array );

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

    // QString avatar_path = database->get_avatar( this->username );
}

void Setter::load_avatar() {
    QString avatar_path = "";

    QJsonArray array;
    array.append( username );
    client_sender->construct_json( "get_avatar", array );
    locked = true;
    while ( locked ) {
        QTime dieTime = QTime::currentTime().addMSecs( 100 );
        while ( QTime::currentTime() < dieTime )
            QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
    if ( msg_queue.front() == 1 ) {
        avatar_path = exec_result;
        msg_queue.pop_front();
    } else {
        QMessageBox::warning( this, "error", "get avatar path failed" );
        msg_queue.pop_front();
        return;
    }

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
    // database->save_person( username, pwd, level, exp, count, nickname );
    QJsonArray array;
    array.append( username );
    array.append( pwd );
    array.append( QString( "%1" ).arg( level ) );
    array.append( QString( "%1" ).arg( exp ) );
    array.append( QString( "%1" ).arg( count ) );
    array.append( nickname );
    client_sender->construct_json( "save_person", array );

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

    QJsonArray array;
    array.append( username );
    array.append( fileNames.front() );
    client_sender->construct_json( "save_avatar", array );
    // database->save_avatar( username, fileNames.front() );
    load_avatar();
}
