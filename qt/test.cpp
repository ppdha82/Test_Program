#include <qapplication.h>
#include <qlabel.h>
#include "include/mainwindow.h"

int main( int argc, char **argv )
{
    QApplication app( argc, argv );
    MainWindow ui;
    QLabel *hello = new QLabel( "<font color=blue>Hello <i>Qt!</i></font>", 0 );
    ui.setMenuWidget( hello );
    hello->show();
    ui.show();

    return app.exec();
}
