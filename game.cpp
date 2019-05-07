#include "game.h"
#include "include.h"
#include "ui_game.h"

game::game( QWidget *parent )
    : QDialog( parent )
    , ui( new Ui::game ) {
    QString s = "";
    ui->setupUi( this );
}

game::~game() { delete ui; }

void game::set_text( const QString _s ) { ui->question->setText( _s ); }

void game::cancel_context() { ui->question->setText( "" ); }

void game::start_game( const QString _s, int level ) {
    this->set_text( _s );
    QTimer::singleShot( 1000 * ( 6 - level ), this, SLOT( cancel_context() ) );

    QTimer *update_left_time = new QTimer( this );
    connect( update_left_time, SIGNAL( timeout() ), this, SLOT( update() ) );
    update_left_time->start( 1000 );

    ui->left_time->display( 6 - level );
    left_time = 6 - level;
    s         = _s;

    qDebug() << "[left time]" << left_time;
}

void game::update() {
    if ( left_time == 0 )
        return;
    else {
        left_time--;
        ui->left_time->display( left_time );
        qDebug() << "[left time]" << left_time;
    }
}

void game::on_cancelBtn_clicked() { close(); }

void game::on_OKBtn_clicked() {
    if ( ui->answer->text() == s )
        accept();
    else
        close();
}
