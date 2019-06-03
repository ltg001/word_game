#ifndef REGISTER_WINDOW_H
#define REGISTER_WINDOW_H

#include "include.h"

namespace Ui {
class register_window;
}

class register_window : public QDialog {
    Q_OBJECT

  public:
    explicit register_window( QWidget *parent = 0 );
    ~register_window();

  private slots:
    void on_OKBtn_clicked();

  private:
    Ui::register_window *ui;
};

#endif // REGISTER_WINDOW_H
