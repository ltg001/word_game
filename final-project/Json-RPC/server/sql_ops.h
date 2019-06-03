#ifndef SQL_OPS_H
#define SQL_OPS_H

#include "include.h"

class sql_ops {
  public:
    sql_ops();
    QJsonArray login( QString username, QString pwd );
    bool       user_register( QString username, QString pwd, int type );
    bool       add_question( QString question, int level, QString username );
    QString    get_question( int level );
    void       save_person( QString username, QString pwd, int level, int exp,
                            int count, QString nickname );
    bool       reset_pwd( QString username, int level, int exp, int count,
                          QString new_pwd );
    QJsonArray load_question_item();
    QJsonArray load_player_rank();
    QJsonArray load_setter_rank();
    QString    get_avatar( QString username );
    void       save_avatar( QString username, QString path );

  private:
    QSqlDatabase info;
    bool         connect();
    bool         can_use_this_name( QString username );
};

QString encrypt( const QString s );
QString decrypt( const QString s );

#endif // SQL_OPS_H
