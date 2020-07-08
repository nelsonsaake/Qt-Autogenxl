#include "mainwindow.h"
#include <QApplication>
#include "gen.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    w.startGen();

    return a.exec();
}


/*
    start with reading and writing json in qt
    then we write the data to json file
    we read it into the ui at start up
    resave it every time it is edited
    and we use the updated version to run the program
*/

/*
    convert the json from the file back to a form that can be written to the ui

    no I'm trying to convert a jsonvalue extracted to a jsonarray

    Then that array would be broken down into vehicle propts

    and those vehicle propts will be used to create ui

    and when one of the ui tabs triggers a save it is saved all the saved are loaded
    used to create a new document and that document is used to replace the old one

    thats it
*/
