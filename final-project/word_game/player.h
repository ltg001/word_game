#ifndef PLAYER_H
#define PLAYER_H

#include "include.h"
#include "person.cpp"

namespace Ui {
class Player;
}

/**
 * @brief
 *
 */
class Player : public QDialog, public Person {
    Q_OBJECT

  public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit Player( QWidget *parent = 0 );
    /**
     * @brief
     *
     */
    ~Player();
    /**
     * @brief
     *
     */
    void update();

  public slots:
    /**
     * @brief
     *
     */
    void get_bonus();

  private slots:
    /**
     * @brief
     *
     */
    void on_game_clicked();

    /**
     * @brief
     *
     */
    void on_questions_clicked();

    /**
     * @brief
     *
     */
    void on_change_clicked();

    /**
     * @brief
     *
     */
    void on_pushButton_clicked();

  private:
    Ui::Player *ui;          /**< TODO: describe */
    int         bonus;       /**< TODO: describe */
    QString     last_failed; /**< TODO: describe */

    /**
     * @brief
     *
     * @param question_level
     */
    void check_levelup( int question_level );
    /**
     * @brief
     *
     * @return bool
     */
    bool play_game();
    /**
     * @brief
     *
     * @param path
     */
    void add_avatar( QString path );
    // int get_level(QString s);
};

#endif // PLAYER_H
