#ifndef SETTER_H
#define SETTER_H

#include "include.h"
#include "person.cpp"

namespace Ui {
class Setter;
}

class Setter : public QDialog, public Person {
    Q_OBJECT

  public:
    explicit Setter( QWidget *parent = 0 );
    ~Setter();
    void update();
    void load_avatar();

  private slots:
    void on_question_clicked();

    void on_submit_clicked();

    void on_change_clicked();

    void on_change_avatar_clicked();

  private:
    Ui::Setter *ui;
    void        check_levelup( int question_level );
    void        add_avatar( QString path );
    // int get_level(QString s);
};

#endif // SETTER_H
