#ifndef GAME_H
#define GAME_H

#include "include.h"
#include "player.h"

namespace Ui {
class game;
}

/**
 * @brief The game class
 * @note show a window and play a game
 * @note func "start_game" needs to be called before the game
 */
class game : public QDialog {
    Q_OBJECT

  public:
    /**
     * @brief constructing the obejct
     *
     * @param parent
     */
    explicit game( QWidget *parent = 0 );
    // void get_content(QString _s);
    /**
     * @brief
     *
     */
    ~game();
    /**
     * @brief
     * just start the game
     * @param _s the quesiton string
     * @param level currect quesion level
     * @param p pointer to the caller
     */
    void start_game( const QString _s, int level, Player *p );

  private slots:
    /**
     * @brief
     * exit
     */
    void on_cancelBtn_clicked();

    /**
     * @brief
     * check whether the answer is right
     */
    void on_OKBtn_clicked();

    /**
     * @brief
     * set string _s to label
     * @param _s
     * the question string
     */
    void set_text( const QString _s );
    /**
     * @brief
     * make the label empty when time is up
     */
    void cancel_context();
    /**
     * @brief
     * update the window shown
     */
    void update();

  private:
    Ui::game *ui;        /**< UI */
    QString   s;         /**< store the question */
    int       left_time; /**< left time */
};

#endif // GAME_H
