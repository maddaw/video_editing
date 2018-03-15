#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QApplication>
#include <QDesktopWidget>

#include <QMenuBar>

#include <QStyle>
#include <QSize>

#include "MediaPlayer.h"
#include "PlaylistView.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setDefaultSize();


private:
    Ui::MainWindow *ui;

    QVBoxLayout *mainLayout;
    QHBoxLayout *topLayout;
    QHBoxLayout *middleLayout;
    QHBoxLayout *bottomLayout;

    CustomMediaPlayer *completePlayer;
    PlaylistView *playlistView;

};

#endif // MAINWINDOW_H
