#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication mainApp(argc, argv);
    MainWindow editorMainWindow;
    editorMainWindow.show();

    return mainApp.exec();
}
