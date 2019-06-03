#ifndef SQL_OPS_H
#define SQL_OPS_H

#include "include.h"
#include "player.h"
#include "setter.h"

/**
 * @brief
 *
 */
class sql_ops {
  private:
    QSqlDatabase info; /**< TODO: describe */
    /**
     * @brief
     *
     * @return bool
     */
    bool connect();
    /**
     * @brief
     *
     * @param username
     * @return bool
     */
    bool can_use_this_name( QString username );
    // bool         comp( QPair<int, QString> lhs, QPair<int, QString> rhs );

  public:
    /**
     * @brief
     *
     */
    sql_ops();
    /**
     * @brief
     *
     * @param username
     * @param pwd
     * @return bool
     */
    bool login( QString username, QString pwd );
    /**
     * @brief
     *
     * @param username
     * @param pwd
     * @param type
     * @return bool
     */
    bool user_register( QString username, QString pwd, int type );
    /**
     * @brief
     *
     * @param question
     * @param level
     * @param username
     * @return bool
     */
    bool add_question( QString question, int level, QString username );
    /**
     * @brief
     *
     * @param username
     * @param pwd
     * @return Player
     */
    Player *login_player( QString username, QString pwd );
    /**
     * @brief
     *
     * @param username
     * @param pwd
     * @return Setter
     */
    Setter *login_setter( QString username, QString pwd );
    /**
     * @brief
     *
     * @param username
     * @param pwd
     * @return int
     */
    int get_type( QString username, QString pwd );
    /**
     * @brief
     *
     * @param level
     * @return QString
     */
    QString get_question( int level );
    /**
     * @brief
     *
     * @param username
     * @param pwd
     * @param level
     * @param exp
     * @param count
     * @param nickname
     */
    void save_person( QString username, QString pwd, int level, int exp,
                      int count, QString nickname );
    /**
     * @brief
     *
     * @param username
     * @param level
     * @param exp
     * @param count
     * @param new_pwd
     * @return bool
     */
    bool reset_pwd( QString username, int level, int exp, int count,
                    QString new_pwd );
    /**
     * @brief
     *
     * @param item
     */
    void load_question_item( QListWidget *item );
    /**
     * @brief
     *
     * @param player
     * @param setter
     */
    void get_rank( QListWidget *player, QListWidget *setter );
    /**
     * @brief
     *
     * @param username
     * @return QString
     */
    QString get_avatar( QString username );
    /**
     * @brief
     *
     * @param username
     * @param path
     */
    void save_avatar( QString username, QString path );
};

/**
 * @brief
 *
 * @param s
 * @return QString
 */
QString encrypt( const QString s );
/**
 * @brief
 *
 * @param s
 * @return QString
 */
QString decrypt( const QString s );

#endif // SQL_OPS_H
