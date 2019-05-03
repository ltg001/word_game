#ifndef RESET_PWD_H
#define RESET_PWD_H

#include "include.h"

namespace Ui {
class reset_pwd;
}

class reset_pwd : public QDialog {
    Q_OBJECT

  public:
    explicit reset_pwd( QWidget *parent = 0 );
    ~reset_pwd();

  private slots:
    void on_OKBtn_clicked();

  private:
    Ui::reset_pwd *ui;
};

#endif // RESET_PWD_H
