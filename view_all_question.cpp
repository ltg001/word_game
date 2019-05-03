#include "view_all_question.h"
#include "sql_ops.h"
#include "ui_view_all_question.h"

extern sql_ops *database;

View_all_question::View_all_question( QWidget *parent )
    : QDialog( parent )
    , ui( new Ui::View_all_question ) {
    ui->setupUi( this );
    auto item = ui->listWidget;
    database->load_question_item( item );
}

View_all_question::~View_all_question() { delete ui; }
