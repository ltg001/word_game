#include "sql_ops.h"

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

QJsonArray sql_ops::login( QString username, QString pwd ) {
    QJsonArray array;
    if ( connect() ) {
        QSqlQuery query;
        if ( query.exec(
                 QString( "select * from user_info where username='%1'" )
                     .arg( username ) ) ) {
            if ( query.next() ) {
                QString temp_pwd = query.value( 1 ).toString();
                if ( temp_pwd == pwd ) {
                    array.append( query.value( 0 ).toString() );
                    array.append( query.value( 1 ).toString() );
                    array.append(
                        QString( "%1" ).arg( query.value( 2 ).toInt() ) );
                    array.append(
                        QString( "%1" ).arg( query.value( 3 ).toInt() ) );
                    array.append(
                        QString( "%1" ).arg( query.value( 4 ).toInt() ) );
                    array.append(
                        QString( "%1" ).arg( query.value( 5 ).toInt() ) );
                    array.append( query.value( 6 ).toString() );
                }
            }
        } else
            qDebug() << "[server database login error]"
                     << query.lastError().text();
    }
    return array;
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

QJsonArray sql_ops::load_question_item() {
    QJsonArray array;

    if ( connect() ) {
        QSqlQuery query;
        if ( query.exec( "select * from question_info" ) ) {
            while ( query.next() ) {
                QJsonObject obj;
                obj.insert( "question", query.value( 0 ).toString() );
                obj.insert( "level", query.value( 1 ).toString() );
                obj.insert( "from", query.value( 2 ).toString() );
                array.append( obj );
            }
        }
    }
    return array;
}

QJsonArray sql_ops::load_player_rank() {
    QJsonArray array;
    if ( connect() ) {
        QSqlQuery query;
        if ( query.exec( "select * from user_info" ) ) {
            while ( query.next() ) {
                if ( query.value( 2 ).toInt() == 1 ) continue;
                QJsonObject obj;
                obj.insert( "username", query.value( 0 ).toString() );
                obj.insert( "count",
                            QString( "%1" ).arg( query.value( 5 ).toInt() ) );
                array.append( obj );
            }
        }
    }
    return array;
}

QJsonArray sql_ops::load_setter_rank() {
    QJsonArray array;
    if ( connect() ) {
        QSqlQuery query;
        if ( query.exec( "select * from user_info" ) ) {
            while ( query.next() ) {
                if ( query.value( 2 ).toInt() == 0 ) continue;
                QJsonObject obj;
                obj.insert( "username", query.value( 0 ).toString() );
                obj.insert( "count",
                            QString( "%1" ).arg( query.value( 5 ).toInt() ) );
                array.append( obj );
            }
        }
    }
    return array;
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

QString encrypt( const QString s ) { return s; }
QString decrypt( const QString s ) { return s; }
