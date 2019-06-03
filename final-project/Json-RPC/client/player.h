#ifndef PLAYER_H
#define PLAYER_H

#include "include.h"
#include "person.cpp"

namespace Ui {
class Player;
}

class Player : public QDialog, public Person {
    Q_OBJECT

  public:
    explicit Player( QWidget *parent = 0 );
    ~Player();
    void update();
    void load_avatar();

  public slots:
    void get_bonus();

  private slots:
    void on_game_clicked();

    void on_questions_clicked();

    void on_change_clicked();

    void on_pushButton_clicked();

  private:
    Ui::Player *ui;
    int         bonus;
    QString     last_failed;

    void check_levelup( int question_level );
    bool play_game();
    void add_avatar( QString path );

    // int get_level(QString s);
};

#endif // PLAYER_H
