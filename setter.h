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
    explicit Setter(QWidget *parent = 0);
    ~Setter();
    void update();

private slots:
    void on_question_clicked();

    void on_submit_clicked();

    void on_change_clicked();

private:
    Ui::Setter *ui;
    //int get_level(QString s);

};

#endif // SETTER_H
