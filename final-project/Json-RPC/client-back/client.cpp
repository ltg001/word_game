#include "client.h"
#include "player.h"
#include "setter.h"
#include "ui_client.h"

extern bool locked;

extern QQueue<QPair<int, QString>> player_rank;
extern QQueue<QPair<int, QString>> setter_rank;
extern QQueue<QString>             question_item;
extern QQueue<int>                 msg_queue;
extern QString                     exec_result;

extern Player *player_ins;
extern Setter *setter_ins;

client::client( QWidget *parent )
    : QDialog( parent )
    , ui( new Ui::client ) {
    ui->setupUi( this );

    bool bind_result = udp_receive->bind( receive_port );
    if ( !bind_result ) return;
    connect( udp_receive, SIGNAL( readyRead() ), this, SLOT( receive_data() ) );
    index = 0;
}

client::~client() { delete ui; }

void client::udp_send( QString to_send ) {
    auto send_udpsocket = new QUdpSocket( this );
    // QString to_send        = construct_json();
    int len = send_udpsocket->writeDatagram(
        to_send.toStdString().c_str(), QHostAddress::Broadcast, send_port );
    if ( len != to_send.length() ) {
        qDebug() << "[client] send failed" << index;
    } else
        qDebug() << "[client] send cuccess";
}

void client::receive_data() {
    QByteArray datagram;
    QString    msg;
    // qDebug() << "[client] func_receive_data";
    while ( udp_receive->hasPendingDatagrams() ) {
        datagram.resize( udp_receive->pendingDatagramSize() );
        udp_receive->readDatagram( datagram.data(), datagram.size() );
        msg = datagram.data();
        qDebug() << "[get data] " << msg;
    }
    parse_json( msg );
}

void client::construct_json( QString method, QJsonArray array ) {
    QJsonObject json;
    json.insert( "jsonrpc", "2.0" );
    json.insert( "address", QString( "%1" ).arg( receive_port ) );
    json.insert( "method", method );
    json.insert( "id", QString( "%1" ).arg( index ) );
    index++;

    json.insert( "params", QJsonValue( array ) );

    QJsonDocument doc;
    doc.setObject( json );
    QByteArray byte_array = doc.toJson( QJsonDocument::Compact );
    QString    str_json( byte_array );
    qDebug() << "[client] send json " << str_json;

    udp_send( str_json );
}

void client::parse_json( QString msg ) {
    QJsonParseError jsonError;
    QJsonDocument   document =
        QJsonDocument::fromJson( msg.toLatin1(), &jsonError );

    QString    func_call;
    QJsonValue params;

    if ( !document.isNull() ) {
        if ( document.isObject() ) {
            QJsonObject obj = document.object();

            if ( obj.contains( "jsonrpc" ) ) {
                if ( obj.contains( "called_method" ) ) {
                    QJsonValue v = obj.value( "called_method" );
                    if ( v.isString() ) func_call = v.toString();
                }

                if ( obj.contains( "result" ) ) {
                    params = obj.value( "result" );
                }
            }
        }
    } else {
        qDebug() << "[client parse json] bad json received";
        return;
    }
    call_func( func_call, params );
}

void client::call_func( QString func_call, QJsonValue params ) {
    qDebug() << "[client call_func] to call " << func_call;
    locked = false;

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

    QString    username, pwd, question, nickname;
    int        level, exp, count, type;
    QJsonArray array;

    switch ( func_list.indexOf( func_call ) ) {
    case 0:
        qDebug() << "unlock for login";
        if ( params.isArray() ) {
            QJsonArray array = params.toArray();
            if ( array.size() == 0 ) {
                msg_queue.push_back( -1 );
                break;
            }

            username = array.at( 0 ).toString();
            pwd      = array.at( 1 ).toString();
            type     = array.at( 2 ).toString().toInt();
            level    = array.at( 3 ).toString().toInt();
            exp      = array.at( 4 ).toString().toInt();
            count    = array.at( 5 ).toString().toInt();
            nickname = array.at( 6 ).toString();

            msg_queue.push_back( 1 );

            if ( type == 0 ) {
                player_ins           = new Player;
                player_ins->username = username;
                player_ins->pwd      = pwd;
                player_ins->level    = level;
                player_ins->exp      = exp;
                player_ins->count    = count;
                // player_ins->type     = type;
                break;
            } else {
                setter_ins           = new Setter;
                setter_ins->username = username;
                setter_ins->pwd      = pwd;
                setter_ins->level    = level;
                setter_ins->exp      = exp;
                setter_ins->count    = count;
                break;
            }
        } else
            msg_queue.push_back( -1 );
        break;

    case 1:
        qDebug() << "unlock for user_register";
        if ( params.isBool() ) {
            if ( params.toBool() == true ) {
                msg_queue.push_back( 1 );
                break;
            }
        } else {
            qDebug() << "[client call func] bad json";
        }
        msg_queue.push_back( -1 );
        break;

    case 2:
        qDebug() << "unlock for add_question";
        if ( params.isBool() ) {
            if ( params.toBool() == true ) {
                msg_queue.push_back( 1 );
                break;
            }
        } else {
            qDebug() << "[client call func] bad json";
        }
        msg_queue.push_back( -1 );
        break;

    case 3:
        if ( params.isString() ) {
            QString temp = params.toString();
            if ( temp != "-1" ) {
                exec_result = temp;
                msg_queue.push_back( 1 );
                break;
            }
        }
        msg_queue.push_back( -1 );
        break;

    case 4: // void save_person
        break;

    case 5:
        if ( params.isBool() ) {
            if ( params.toBool() == true ) {
                msg_queue.push_back( 1 );
                break;
            }
        }
        msg_queue.push_back( -1 );
        break;

    case 6:
        if ( params.isArray() ) {
            array = params.toArray();
            for ( int i = 0; i < array.size(); i++ ) {
                QJsonObject obj = array.at( i ).toObject();
                question_item.push_back(
                    "question: " + obj.value( "question" ).toString() +
                    " level: " + obj.value( "level" ).toString() +
                    " from: " + obj.value( "from" ).toString() );
            }
            // qSort( question_item.begin(), question_item.end(), comp );
            msg_queue.push_back( 1 );
            break;
        }
        msg_queue.push_back( -1 );
        break;

    case 7:
        if ( params.isArray() ) {
            array = params.toArray();
            for ( int i = 0; i < array.size(); i++ ) {
                QJsonObject obj = array.at( i ).toObject();
                qDebug() << obj;
                player_rank.push_back(
                    qMakePair( obj.value( "count" ).toString().toInt(),
                               obj.value( "username" ).toString() ) );
                qDebug() << "[push to player_rank]" << player_rank.last();
            }
            msg_queue.push_back( 1 );
            // qDebug() << "[!!!player_rank]" << player_rank.size();
            break;
        }
        msg_queue.push_back( -1 );
        break;

    case 8:
        if ( params.isArray() ) {
            array = params.toArray();
            for ( int i = 0; i < array.size(); i++ ) {
                QJsonObject obj = array.at( i ).toObject();
                qDebug() << obj;
                setter_rank.push_back(
                    qMakePair( obj.value( "count" ).toString().toInt(),
                               obj.value( "username" ).toString() ) );
                qDebug() << "[push to setter_rank]" << setter_rank.last();
            }
            // qDebug() << "[!!!setter_rank]" << setter_rank.size();
            msg_queue.push_back( 1 );
            break;
        }
        msg_queue.push_back( -1 );
        break;

    case 9:
        if ( params.isString() ) {
            exec_result = params.toString();
            msg_queue.push_back( 1 );
            qDebug() << "[client get avatar]: " << exec_result;
            break;
        }
        msg_queue.push_back( -1 );
        break;

    case 10: // void save_avatar
        break;

    default:
        break;
    }
}

bool comp( QPair<int, QString> lhs, QPair<int, QString> rhs ) {
    if ( lhs.first == rhs.first ) return lhs.second < rhs.second;
    return lhs.first < rhs.first;
}
