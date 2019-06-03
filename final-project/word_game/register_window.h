#ifndef REGISTER_WINDOW_H
#define REGISTER_WINDOW_H

#include "include.h"

namespace Ui {
class register_window;
}

/**
 * @brief
 *
 */
class register_window : public QDialog {
    Q_OBJECT

  public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit register_window( QWidget *parent = 0 );
    /**
     * @brief
     *
     */
    ~register_window();

  private slots:
    /**
     * @brief
     *
     */
    void on_OKBtn_clicked();

  private:
    Ui::register_window *ui; /**< TODO: describe */
};

#endif // REGISTER_WINDOW_H
