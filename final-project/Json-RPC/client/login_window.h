#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include "include.h"

namespace Ui {
class login_window;
}

class login_window : public QDialog {
    Q_OBJECT

  public:
    explicit login_window( QWidget *parent = 0 );
    ~login_window();

  private slots:
    void on_OKBtn_clicked();

    void on_register_2_clicked();

    void on_forget_pwd_clicked();

  private:
    Ui::login_window *ui;
};

#endif // LOGIN_WINDOW_H
