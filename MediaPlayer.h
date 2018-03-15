#ifndef CUSTOMMEDIAPLAYER_H
#define CUSTOMMEDIAPLAYER_H

#include <QDebug>

#include <QString>
#include <QFile>
#include <QFileDialog>

#include <QUrl>

#include <QFrame>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSizePolicy>

#include <QMediaPlayer>

#include <QVideoProbe>
#include <QVideoWidget>


#include <QMediaPlaylist>

#include "PlayerControls.h"

class CustomMediaPlayer : public QWidget
{
        Q_OBJECT
    private:
        QVBoxLayout *playerMainLayout;

        QFrame *outputHolder;

        QMediaPlayer *playerMain;
        QMediaPlaylist *playlistMain;

        QVideoWidget *playerOutput;

        CustomPlayerControls *playerControls;



    public:
        explicit CustomMediaPlayer(QWidget *parent = nullptr);

        QMediaPlaylist* getPlaylist();
        QMediaPlayer* getPlayer();
        CustomPlayerControls* getControls();
    signals:
        void mediaAdded(QString);
    public slots:
        void addMedia();


};

#endif // CUSTOMMEDIAPLAYER_H
