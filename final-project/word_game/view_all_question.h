#ifndef VIEW_ALL_QUESTION_H
#define VIEW_ALL_QUESTION_H

#include "include.h"
#include <QDialog>

namespace Ui {
class View_all_question;
}

/**
 * @brief
 *
 */
class View_all_question : public QDialog {
    Q_OBJECT

  public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit View_all_question( QWidget *parent = 0 );
    /**
     * @brief
     *
     */
    ~View_all_question();

  private:
    Ui::View_all_question *ui; /**< UI */
};

#endif // VIEW_ALL_QUESTION_H
