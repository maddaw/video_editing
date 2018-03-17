#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H

#include "MediaPlayer.h"

#include <QListWidget>

#include <QDebug>

#include <QList>
#include <QLabel>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QMediaPlaylist>
#include <QMediaPlayer>

#include <QPushButton>

class PlaylistView : public QWidget
{
    private:
       QVBoxLayout *vLayout;
       QHBoxLayout *hLayout;

       CustomMediaPlayer *connectedPlayer;
       QListWidget *mediaLabels;

       QPushButton *selectMedia, *deleteMedia;

    public:
        PlaylistView(QWidget *parent,  CustomMediaPlayer *tempConnectedPlayer);

    signals:

    public slots:
        void addLabel(QString fileName);
        void selectVideo();
        void deleteVideo();
};

#endif // PLAYLISTVIEW_H
