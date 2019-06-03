#ifndef RESET_PWD_H
#define RESET_PWD_H

#include "include.h"

namespace Ui {
class reset_pwd;
}

/**
 * @brief
 *
 */
class reset_pwd : public QDialog {
    Q_OBJECT

  public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit reset_pwd( QWidget *parent = 0 );
    /**
     * @brief
     *
     */
    ~reset_pwd();

  private slots:
    /**
     * @brief
     *
     */
    void on_OKBtn_clicked();

  private:
    Ui::reset_pwd *ui; /**< TODO: describe */
};

#endif // RESET_PWD_H
