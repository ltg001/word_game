#include "mainwindow.h"
#include "server.h"
#include "sql_ops.h"
#include <QApplication>

sql_ops *database;

int main( int argc, char *argv[] ) {
    QApplication a( argc, argv );
    MainWindow   w;
    // w.show();
    server s;
    database = new sql_ops;
    if ( s.exec() == QDialog::Accepted ) {
    }
    return 0;
}
