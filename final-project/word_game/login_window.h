#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include "include.h"

namespace Ui {
class login_window;
}
/**
 * @brief The login_window class show the Login window and see if the password
 * is right
 */
class login_window : public QDialog {
    Q_OBJECT

  public:
    /**
     * @brief
     * constructing the object
     * @param parent
     */
    explicit login_window( QWidget *parent = 0 );
    /**
     * @brief
     *
     */
    ~login_window();

  private slots:
    /**
     * @brief
     * check whether the username and pwd match
     */
    void on_OKBtn_clicked();

    /**
     * @brief
     * show register window
     */
    void on_register_2_clicked();

    /**
     * @brief
     * show forget_pwd window
     */
    void on_forget_pwd_clicked();

  private:
    Ui::login_window *ui; /**< UI */
};

#endif // LOGIN_WINDOW_H
