#ifndef SQL_OPS_H
#define SQL_OPS_H

#include "include.h"
#include "player.h"
#include "setter.h"

class sql_ops {
  private:
    QSqlDatabase info;
    bool         connect();
    bool         can_use_this_name( QString username );
    // bool         comp( QPair<int, QString> lhs, QPair<int, QString> rhs );

  public:
    sql_ops();
    bool    login( QString username, QString pwd );
    bool    user_register( QString username, QString pwd, int type );
    bool    add_question( QString question, int level, QString username );
    Player *login_player( QString username, QString pwd );
    Setter *login_setter( QString username, QString pwd );
    int     get_type( QString username, QString pwd );
    QString get_question( int level );
    void    save_person( QString username, QString pwd, int level, int exp,
                         int count, QString nickname );
    bool    reset_pwd( QString username, int level, int exp, int count,
                       QString new_pwd );
    void    load_question_item( QListWidget *item );
    void    get_rank( QListWidget *player, QListWidget *setter );
};

QString encrypt( const QString s );
QString decrypt( const QString s );

#endif // SQL_OPS_H
