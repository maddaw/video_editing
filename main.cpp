#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication playerAPP(argc, argv);
    MainWindow playerMainWindow;
    playerMainWindow.setWindowState(Qt::WindowMaximized);
    playerMainWindow.show();

    return playerAPP.exec();
}

/*
    qmake - pomaga w linkowaniu, buildzie, Target - nazwa koncowej aplikacji, mozna dodac CONFIG += debug
                mozna uzyc scope'a dla wybranej platformy np win 32 {SOURCES += mainwin.cpp } - skompiluje/zbuilduje plik tylko na windowsa (?)
                                                             unix {SOURCES += mainunix.cpp } - skompiluje/zbuilduje plik na UNIXA
                                                             exist(plik) {} - instrukcja warunkowa sprawdzająca czy plik istnieje



*/
