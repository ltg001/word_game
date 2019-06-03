#ifndef SETTER_H
#define SETTER_H

#include "include.h"
#include "person.cpp"

namespace Ui {
class Setter;
}

/**
 * @brief
 *
 */
class Setter : public QDialog, public Person {
    Q_OBJECT

  public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit Setter( QWidget *parent = 0 );
    /**
     * @brief
     *
     */
    ~Setter();
    /**
     * @brief
     *
     */
    void update();

  private slots:
    /**
     * @brief
     *
     */
    void on_question_clicked();

    /**
     * @brief
     *
     */
    void on_submit_clicked();

    /**
     * @brief
     *
     */
    void on_change_clicked();

    /**
     * @brief
     *
     */
    void on_change_avatar_clicked();

  private:
    Ui::Setter *ui; /**< TODO: describe */
    /**
     * @brief
     *
     * @param question_level
     */
    void check_levelup( int question_level );
    /**
     * @brief
     *
     * @param path
     */
    void add_avatar( QString path );
    // int get_level(QString s);
};

#endif // SETTER_H
