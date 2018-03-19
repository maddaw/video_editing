#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "MediaContainer.h"
#include "MediaPlayer.h"
#include "MediaControls.h"
#include "EditorControls.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);



        ~MainWindow();

    private:
        Ui::MainWindow *ui;

        QString mediaFolder;

        QVBoxLayout *mainLayout;

        QHBoxLayout *topLayout;
        QHBoxLayout *middleLayout;
        QHBoxLayout *bottomLayout;

        MediaPlayer *mediaPlayer;
        MediaContainer *mediaContainer;
        MediaControls *mediaControls;
        EditorControls *editControls;

    public slots:


};
#endif // MAINWINDOW_H
