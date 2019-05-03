#ifndef GAME_H
#define GAME_H

#include "include.h"

namespace Ui {
class game;
}

class game : public QDialog
{
    Q_OBJECT

public:
    explicit game(QWidget *parent = 0);
    // void get_content(QString _s);
    ~game();
    void start_game(const QString _s, int level);

private slots:
    void on_cancelBtn_clicked();

    void on_OKBtn_clicked();

    void set_text(const QString _s);
    void cancel_context();
private:
    Ui::game *ui;
    QString s;
};

#endif // GAME_H
