#include "sql_ops.h"
#include "player.h"
#include "setter.h"

sql_ops::sql_ops() {
    info = QSqlDatabase::addDatabase( "QSQLITE" );
    info.setDatabaseName( "info.db" );

    if ( !info.open() )
        qDebug() << "failed to open database" << info.lastError().text();
    else
        qDebug() << "connected to database";

    QSqlQuery query;
    if ( !query.exec( "create table if not exists user_info("
                      "username varchar primary key,"
                      "pwd varchar, "
                      "type int,"
                      "level int,"
                      "exp int,"
                      "count int,"
                      "nickname varchar)" ) )
        qDebug() << "[create user_info]" << query.lastError().text();

    if ( !query.exec( "create table if not exists question_info("
                      "question varchar primary key, "
                      "level int, "
                      "from_who varchar)" ) )
        qDebug() << "[create question_info]" << query.lastError().text();
    if ( !query.exec( "create table if not exists avatar_info("
                      "username varchar primary key, "
                      "address varchar)" ) )
        qDebug() << "[create avatar_info]" << query.lastError().text();
}

bool sql_ops::connect() {
    if ( !info.open() ) {
        qDebug() << "[database error]" << info.lastError().text();
        return false;
    }
    return true;
}

bool sql_ops::can_use_this_name( QString username ) {
    if ( connect() ) {
        QSqlQuery query;
        query.exec(
            QString( "select username from user_info where username ='%1'" )
                .arg( username ) );
        if ( !query.next() )
            return true;
        else
            return false;
    } else
        return false;
}

bool sql_ops::user_register( QString username, QString pwd, int type ) {
    username = encrypt( username );
    pwd      = encrypt( pwd );

    if ( !can_use_this_name( username ) ) return false;

    if ( connect() ) {
        QSqlQuery query;
        if ( !query.exec(
                 "insert into user_info(username, pwd, type, level, exp, "
                 "count, nickname)" +
                 QString( "values('%1', '%2', %3, 1, 0, 0, '')" )
                     .arg( username )
                     .arg( pwd )
                     .arg( type ) ) ) {
            qDebug() << "[insert failed] " << query.lastError().text();
            qDebug() << QString( "values('%1', '%2', %3, 1, 0, 0, '')" )
                            .arg( username )
                            .arg( pwd )
                            .arg( type );
            return false;
        } else
            qDebug() << "[insert successful] "
                     << QString( "values('%1', '%2', %3, 0, 0, 0)" )
                            .arg( username )
                            .arg( pwd )
                            .arg( type );
    }
    return true;
}

bool sql_ops::add_question( QString question, int level, QString username ) {
    if ( connect() ) {
        QSqlQuery query;
        if ( query.exec(
                 "insert into question_info(question, level, from_who)" +
                 QString( "values('%1', %2, '%3')" )
                     .arg( question )
                     .arg( level )
                     .arg( username ) ) ) {
            qDebug() << "[add question successful]";
            return true;
        } else {
            qDebug() << "[add question failed]" << query.lastError().text();
            return false;
        }
    }
    return false;
}

bool sql_ops::login( QString username, QString pwd ) {
    username = encrypt( username );
    pwd      = encrypt( pwd );
    if ( connect() ) {
        QSqlQuery query;
        if ( !query.exec(
                 QString( "select * from user_info where username='%1'" )
                     .arg( username ) ) )
            qDebug() << "[log in failed] " << query.lastError().text();
        if ( query.next() ) {
            QString temp_pwd = query.value( 1 ).toString();
            qDebug() << "[from database temp pwd]: " << temp_pwd << "[pwd]"
                     << pwd;
            if ( temp_pwd == pwd ) {
                qDebug() << "[login]" << username;
                return true;
                // qDebug() << "test";
            } else
                return false;
        } else
            return false;
    }
    return false;
}

Player *sql_ops::login_player( QString username, QString pwd ) {
    if ( !login( username, pwd ) ) return nullptr;

    Player *temp = new Player();
    if ( connect() ) {
        QSqlQuery query;
        if ( query.exec( "select * from user_info where username = " +
                         QString( "'%1'" ).arg( username ) ) ) {
            qDebug() << "[login successful]"
                     << QString( "%1 " ).arg( username ) + "login";
            while ( query.next() ) {
                temp->username = query.value( 0 ).toString();
                temp->pwd      = query.value( 1 ).toString();
                temp->level    = query.value( 3 ).toInt();
                temp->exp      = query.value( 4 ).toInt();
                temp->count    = query.value( 5 ).toInt();
                temp->nickname = query.value( 6 ).toString();
                qDebug() << "[from data base load player]" << temp->username
                         << " " << temp->nickname;
                qDebug() << "[player address]" << temp;
            }
        } else {
            qDebug() << "[login failed]";
            delete temp;
            return nullptr;
        }
    }

    return temp;
}

Setter *sql_ops::login_setter( QString username, QString pwd ) {
    if ( !login( username, pwd ) ) return nullptr;

    Setter *temp = new Setter;
    if ( connect() ) {
        QSqlQuery query;
        if ( query.exec( "select * from user_info where username = " +
                         QString( "'%1'" ).arg( username ) ) ) {
            qDebug() << QString( "%1 " ).arg( username ) + "login";

            while ( query.next() ) {
                temp->username = query.value( 0 ).toString();
                temp->pwd      = query.value( 1 ).toString();
                temp->level    = query.value( 3 ).toInt();
                temp->exp      = query.value( 4 ).toInt();
                temp->count    = query.value( 5 ).toInt();
                temp->nickname = query.value( 6 ).toString();
            }
        } else {
            qDebug() << "login failed";
            delete temp;
            return nullptr;
        }
    }
    return temp;
}

int sql_ops::get_type( QString username, QString pwd ) {
    if ( !login( username, pwd ) ) return -1;

    if ( connect() ) {
        QSqlQuery query;
        query.exec( QString( "select * from user_info where username='%1'" )
                        .arg( username ) );
        if ( query.next() ) { // player -> 0 & setter -> 1
            qDebug() << "[get type]" << query.value( 2 ).toInt();
            return query.value( 2 ).toInt();
        } else
            return -1;
    }
    return -1;
}

QString sql_ops::get_question( int level ) {
    QString question;
    qDebug() << "[get_question] get " << level;
    if ( connect() ) {
        QSqlQuery query;
        if ( query.exec(
                 QString( "select * from question_info where level = %1 order "
                          "by random() limit 1" )
                     .arg( level ) ) ) {
            while ( query.next() ) {
                question = query.value( 0 ).toString();
                return question;
            }
            qDebug() << "[database failed] return '-1' ";
            return -1;
        } else {
            qDebug() << "[database failed] " << query.lastError().text();
        }
    }
    qDebug() << "[database failed] return '-1' ";
    return "-1";
}

void sql_ops::save_person( QString username, QString pwd, int level, int exp,
                           int count, QString nickname ) {
    if ( connect() ) {
        QSqlQuery query;
        qDebug() << "[save person] to run: "
                 << QString( "update user_info set pwd='%1', level=%2, exp=%3, "
                             "count=%4, nickname='%5' where username='%6'" )
                        .arg( pwd )
                        .arg( level )
                        .arg( exp )
                        .arg( count )
                        .arg( nickname )
                        .arg( username );
        if ( !query.exec(
                 QString( "update user_info set pwd='%1', level=%2, exp=%3, "
                          "count=%4, nickname='%5' where username='%6'" )
                     .arg( pwd )
                     .arg( level )
                     .arg( exp )
                     .arg( count )
                     .arg( nickname )
                     .arg( username ) ) ) {
            qDebug() << "[save person error]" << query.lastError().text();
        } else
            qDebug() << "[database update] success";
    }
}

bool sql_ops::reset_pwd( QString username, int level, int exp, int count,
                         QString new_pwd ) {
    if ( connect() ) {
        QSqlQuery query;
        query.exec( QString( "select * from user_info where username='%1'" )
                        .arg( username ) );
        if ( query.next() ) {
            if ( query.value( 3 ).toInt() == level &&
                 query.value( 4 ).toInt() == exp &&
                 query.value( 5 ).toInt() == count ) {
                if ( !query.exec( QString( "update user_info set pwd='%1' "
                                           "where username='%2'" )
                                      .arg( new_pwd )
                                      .arg( username ) ) ) {
                    qDebug() << "[reset_pwd]" << query.lastError().text();
                    return false;
                } else {
                    qDebug() << "[reset_pwd]"
                             << QString( "%1 changed pwd to %2" )
                                    .arg( username )
                                    .arg( new_pwd );
                    return true;
                }
            }
        }
    }
    return false;
}

void sql_ops::load_question_item( QListWidget *item ) {
    if ( connect() ) {
        QSqlQuery query;
        if ( query.exec( "select * from question_info" ) ) {
            while ( query.next() ) {
                item->addItem( new QListWidgetItem(
                    QString( "question: %1, level: %2, from: %3" )
                        .arg( query.value( 0 ).toString() )
                        .arg( query.value( 1 ).toInt() )
                        .arg( query.value( 2 ).toString() ) ) );
                qDebug() << "[load_question]"
                         << QString( "question: %1, level: %2, from: %3" )
                                .arg( query.value( 0 ).toString() )
                                .arg( query.value( 1 ).toInt() )
                                .arg( query.value( 2 ).toString() );
            }
        }
    }
}

bool comp( QPair<int, QString> lhs, QPair<int, QString> rhs ) {
    if ( lhs.first == rhs.first ) return lhs.second < rhs.second;
    return lhs.first > rhs.first;
}

void sql_ops::get_rank( QListWidget *player, QListWidget *setter ) {
    QQueue<QPair<int, QString>> player_list;
    QQueue<QPair<int, QString>> setter_list;

    if ( connect() ) {
        QSqlQuery query;
        if ( query.exec( "select * from user_info" ) ) {
            while ( query.next() ) {
                if ( query.value( 2 ).toInt() == 0 ) {
                    player_list.append(
                        qMakePair( query.value( 5 ).toInt(),
                                   query.value( 0 ).toString() ) );
                } else {
                    setter_list.append(
                        qMakePair( query.value( 5 ).toInt(),
                                   query.value( 0 ).toString() ) );
                }
            }
        } else
            qDebug() << "[get rank] " << query.lastError().text();

        if ( !player_list.empty() )
            qSort( player_list.begin(), player_list.end(), comp );
        if ( !setter_list.empty() )
            qSort( setter_list.begin(), setter_list.end(), comp );

        int player_index = 1, setter_index = 1;

        while ( !player_list.empty() ) {
            player->addItem( new QListWidgetItem(
                QString( "rank: %1, username: %2, solved_problems: %3" )
                    .arg( player_index )
                    .arg( player_list.front().second )
                    .arg( player_list.front().first ) ) );
            player_list.pop_front();
            player_index += 1;
        }

        while ( !setter_list.empty() ) {
            setter->addItem( new QListWidgetItem(
                QString( "rank: %1, username: %2, set_problems: %3" )
                    .arg( setter_index )
                    .arg( setter_list.front().second )
                    .arg( setter_list.front().first ) ) );
            setter_list.pop_front();
            setter_index += 1;
        }
    }
}

QString sql_ops::get_avatar( QString username ) {
    if ( connect() ) {
        QSqlQuery query;
        if ( !query.exec( QString( "select * from avatar_info "
                                   "where username='%1'" )
                              .arg( username ) ) )
            qDebug() << "[get_avatar]" << query.lastError().text();

        qDebug() << "[get_avatar] try:"
                 << QString( "select * from avatar_info "
                             "where username='%1'" )
                        .arg( username )
                 << "[username]" << username;

        if ( query.next() ) {
            qDebug() << "[get_avatar_1]" << query.value( 1 ).toString();
            return query.value( 1 ).toString();
        }
        qDebug() << "get_avatar_2_ no username";
        return "";
    }
    return "";
}

void sql_ops::save_avatar( QString username, QString path ) {
    if ( connect() ) {
        QSqlQuery query;

        query.exec( QString( "select * from avatar_info where username='%1'" )
                        .arg( username ) );

        if ( query.next() ) {
            if ( query.exec( QString( "update avatar_info set address='%1' "
                                      "where username='%2'" )
                                 .arg( path )
                                 .arg( username ) ) ) {
                qDebug() << "[update_avatar] success"
                         << QString( "update avatar_info set address='%1' "
                                     "where username='%2'" )
                                .arg( path )
                                .arg( username );
            } else
                qDebug() << "[save avatar] failed" << query.lastError().text();
        } else {
            if ( query.exec(
                     QString( "insert into avatar_info(username, address) "
                              "values('%1', '%2')" )
                         .arg( username )
                         .arg( path ) ) ) {
                qDebug() << "[insert avatar] success"
                         << QString(
                                "insert into avatar_info(username, address) "
                                "values('%1', '%2')" )
                                .arg( username )
                                .arg( path );
            } else
                qDebug() << "[save avatar] failed" << query.lastError().text();
        }
    }
}

// QQueue<QPair<int, QString>> *sql_ops::get_rank() {
//    QQueue<QPair<int, QString>> *ans = new QQueue<QPair<int, QString>>;
//    if ( connect() ) {
//        QSqlQuery query;
//        if ( query.exec( "select * from user_info" ) ) {
//            while ( query.next() ) {
//                int     count    = query.value( 5 ).toInt();
//                QString username = query.value( 0 ).toString();
//                ans->append( qMakePair( count, username ) );
//            }
//        } else
//            qDebug() << "[get rank] " << query.lastError().text();
//    }
//    if ( !ans->empty() ) qSort( ans->begin(), ans->end(), comp );
//    return ans;
//}

QString encrypt( const QString s ) { return s; }
QString decrypt( const QString s ) { return s; }
