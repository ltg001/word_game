/**
 * @file nothing here
 */

#ifndef STYLE_H
#define STYLE_H

#include "include.h"

/**
 * @brief
 *
 */
class style {
  public:
    /**
     * @brief
     *
     */
    static void set_style() {
        QFile f( ":qdarkstyle/style.qss" );
        if ( !f.exists() ) {
            qDebug() << "Unable to set stylesheet, file not found\n";
        } else {
            f.open( QFile::ReadOnly | QFile::Text );
            QTextStream ts( &f );
            qApp->setStyleSheet( ts.readAll() );
            qDebug() << "load style";
        }
    }
};

#endif // STYLE_H
