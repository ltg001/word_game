#ifndef CLIENT_H
#define CLIENT_H

#include "include.h"
#include <QDialog>

namespace Ui {
class client;
}

class client : public QDialog {
    Q_OBJECT

  public:
    explicit client( QWidget *parent = 0 );
    ~client();
    void construct_json( QString method, QJsonArray array );

  private slots:
    void receive_data();

  private:
    Ui::client *ui;

    QUdpSocket *udp_receive  = new QUdpSocket( this );
    int         receive_port = 9000;
    int         send_port    = 8000;

    void udp_send( QString to_send );
    void parse_json( QString msg );
    void call_func( QString func_call, QJsonValue params );
    int  index;
};

bool comp( QPair<int, QString> lhs, QPair<int, QString> rhs );

#endif // CLIENT_H
