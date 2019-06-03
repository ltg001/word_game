

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

/**
 * @brief game::set_text
 * @param _s The string to be shown on the label.
 */
void game::set_text( const QString _s ) { ui->question->setText( _s ); }

void game::cancel_context() { ui->question->setText( "" ); }

/**
 * @brief game::start_game
 * @param _s The string to be shown on the label.
 * @param level Current question's level
 * @param p The pointer points to the caller to change the bonus.
 */
void game::start_game( const QString _s, int level, Player *p ) {
    this->set_text( _s );
    QTimer::singleShot( 1000 * ( 6 - level ), this, SLOT( cancel_context() ) );

    QTimer *update_left_time = new QTimer( this );
    connect( update_left_time, SIGNAL( timeout() ), this, SLOT( update() ) );
    update_left_time->start( 1000 );

    QTimer *bonus_timer = new QTimer( this );
    connect( bonus_timer, SIGNAL( timeout() ), p, SLOT( get_bonus() ) );
    bonus_timer->start( 500 * ( 6 - level ) );

    ui->left_time->display( 6 - level );
    left_time = 6 - level;
    s         = _s;

    qDebug() << "[left time]" << left_time;
}

/**
 * @brief game::update called every second to change the left time shown on the
 * timer
 */
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

/**
 * @brief game::on_OKBtn_clicked Check if the player has passed
 */
void game::on_OKBtn_clicked() {
    if ( ui->answer->text() == s )
        accept();
    else
        close();
}
