#ifndef VIEW_ALL_QUESTION_H
#define VIEW_ALL_QUESTION_H

#include "include.h"
#include <QDialog>

namespace Ui {
class View_all_question;
}

class View_all_question : public QDialog {
    Q_OBJECT

  public:
    explicit View_all_question( QWidget *parent = 0 );
    ~View_all_question();

  private:
    Ui::View_all_question *ui;
};

#endif // VIEW_ALL_QUESTION_H
