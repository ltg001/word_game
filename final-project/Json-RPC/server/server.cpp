#include "server.h"
#include "QTime"
#include "sql_ops.h"
#include "ui_server.h"

extern sql_ops *database;

bool locked = false;

server::server( QWidget *parent )
    : QDialog( parent )
    , ui( new Ui::server ) {
    ui->setupUi( this );

    bool bind_result = udp_receive->bind( receive_port );
    if ( !bind_result ) return;
    connect( udp_receive, SIGNAL( readyRead() ), this, SLOT( receive_data() ) );
}

server::~server() { delete ui; }

void server::receive_data() {
    while ( udp_receive->hasPendingDatagrams() ) {
        QByteArray datagram;
        datagram.resize( udp_receive->pendingDatagramSize() );
        udp_receive->readDatagram( datagram.data(), datagram.size() );
        QString msg = datagram.data();
        qDebug() << "[server] get: " << msg;

        parse_json( msg );
    }
}

void server::parse_json( QString msg ) {
    QJsonParseError jsonError;
    QJsonDocument   document =
        QJsonDocument::fromJson( msg.toLatin1(), &jsonError );

    QString    func_call;
    QJsonArray params;
    int        id;

    if ( !document.isNull() ) {
        if ( document.isObject() ) {
            QJsonObject obj = document.object();

            if ( obj.contains( "jsonrpc" ) ) {
                if ( obj.contains( "method" ) ) {
                    QJsonValue v = obj.value( "moethod" );
                    if ( v.isString() ) func_call = v.toString();
                }
            }

            if ( obj.contains( "method" ) ) {
                QJsonValue v = obj.value( "method" );
                if ( v.isString() ) func_call = v.toString();
            }

            if ( obj.contains( "params" ) ) {
                QJsonValue v = obj.value( "params" );
                if ( v.isArray() ) params = v.toArray();
            }

            if ( obj.contains( "address" ) ) {
                QJsonValue v = obj.value( "address" );
                if ( v.isString() ) send_port = v.toString().toInt();
            }

            if ( obj.contains( "id" ) ) {
                QJsonValue v = obj.value( "id" );
                if ( v.isString() ) id = v.toString().toInt();
            }
        }
    }

    call_func( func_call, id, params );
}

void server::udp_send( QString msg ) {
    auto    udp_send = new QUdpSocket( this );
    QString to_send  = msg;
    if ( to_send.isEmpty() ) return;
    int len = udp_send->writeDatagram( to_send.toStdString().c_str(),
                                       QHostAddress::Broadcast, send_port );
    if ( len != to_send.length() ) {
        // QMessageBox::information( this, "reply", "reply failed" );
        qDebug() << "[server udp_send] reply failed";
        len = udp_send->writeDatagram( to_send.toStdString().c_str(),
                                       QHostAddress::Broadcast, send_port );
    }
}

void server::call_func( QString func_call, int id, QJsonArray params ) {
    QJsonObject json;

    qDebug() << "[server call_func] func_call: " << func_call
             << "params: " << params;

    QStringList func_list;
    func_list << "login"
              << "user_register"
              << "add_question"
              << "get_question"
              << "save_person"
              << "reset_pwd"
              << "load_question_item"
              << "load_player_rank"
              << "load_setter_rank"
              << "get_avatar"
              << "save_avatar";

    QString username, pwd, nickname, path, question, new_pwd;
    int     type, level, exp, count;

    switch ( func_list.indexOf( func_call ) ) {
    case 0:
        username = params.at( 0 ).toString();
        pwd      = params.at( 1 ).toString();
        json.insert( "result", QJsonValue( database->login( username, pwd ) ) );
        break;

    case 1:
        while ( locked ) {
            QTime dieTime = QTime::currentTime().addMSecs( 100 );
            while ( QTime::currentTime() < dieTime )
                QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
        }
        locked   = true;
        username = params.at( 0 ).toString();
        pwd      = params.at( 1 ).toString();
        type     = params.at( 2 ).toString().toInt();
        json.insert( "result", database->user_register( username, pwd, type ) );
        locked = false;
        break;

    case 2:
        while ( locked ) {
            QTime dieTime = QTime::currentTime().addMSecs( 100 );
            while ( QTime::currentTime() < dieTime )
                QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
        }
        locked   = true;
        question = params.at( 0 ).toString();
        level    = params.at( 1 ).toString().toInt();
        username = params.at( 2 ).toString();
        json.insert( "result",
                     database->add_question( question, level, username ) );
        locked = false;
        break;

    case 3:
        level = params.at( 0 ).toString().toInt();
        json.insert( "result", database->get_question( level ) );
        break;

    case 4:
        // qDebug() << "==============get save_person";
        while ( locked ) {
            QTime dieTime = QTime::currentTime().addMSecs( 100 );
            while ( QTime::currentTime() < dieTime )
                QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
        }
        locked   = true;
        username = params.at( 0 ).toString();
        pwd      = params.at( 1 ).toString();
        level    = params.at( 2 ).toString().toInt();
        exp      = params.at( 3 ).toString().toInt();
        count    = params.at( 4 ).toString().toInt();
        nickname = params.at( 5 ).toString();
        database->save_person( username, pwd, level, exp, count, nickname );
        json.insert( "result", true );
        locked = false;
        break;

    case 5:
        while ( locked ) {
            QTime dieTime = QTime::currentTime().addMSecs( 100 );
            while ( QTime::currentTime() < dieTime )
                QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
        }
        locked   = true;
        username = params.at( 0 ).toString();
        level    = params.at( 1 ).toString().toInt();
        exp      = params.at( 2 ).toString().toInt();
        count    = params.at( 3 ).toString().toInt();
        new_pwd  = params.at( 4 ).toString();
        json.insert( "result", database->reset_pwd( username, level, exp, count,
                                                    new_pwd ) );
        locked = false;
        break;

    case 6:
        json.insert( "result", QJsonValue( database->load_question_item() ) );
        break;

    case 7:
        json.insert( "result", QJsonValue( database->load_player_rank() ) );
        break;

    case 8:
        json.insert( "result", QJsonValue( database->load_setter_rank() ) );
        break;

    case 9:
        username = params.at( 0 ).toString();
        json.insert( "result", database->get_avatar( username ) );
        break;
    case 10:
        while ( locked ) {
            QTime dieTime = QTime::currentTime().addMSecs( 100 );
            while ( QTime::currentTime() < dieTime )
                QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
        }
        locked   = true;
        username = params.at( 0 ).toString();
        path     = params.at( 1 ).toString();
        database->save_avatar( username, path );
        locked = false;
        break;
    default:
        break;
    }

    json.insert( "id", QString( "%1" ).arg( id ) );
    json.insert( "jsonrpc", "2.0" );
    json.insert( "called_method", QString( "%1" ).arg( func_call ) );

    QJsonDocument doc;
    doc.setObject( json );
    QByteArray byte_array = doc.toJson( QJsonDocument::Compact );
    QString    str_json( byte_array );
    qDebug() << "[server] reply json " << str_json;

    udp_send( str_json );
}
