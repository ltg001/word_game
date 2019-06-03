#ifndef SERVER_H
#define SERVER_H

#include "include.h"
#include <QDialog>

namespace Ui {
class server;
}

class server : public QDialog {
    Q_OBJECT

  public:
    explicit server( QWidget *parent = 0 );
    ~server();

  private slots:
    void receive_data();

  private:
    Ui::server *ui;

    QUdpSocket *udp_receive = new QUdpSocket( this );
    int         send_port;
    int         receive_port = 8000;

    void parse_json( QString msg );
    void udp_send( QString msg );
    void call_func( QString func_call, int id, QJsonArray params );
};

#endif // SERVER_H
