#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QDebug>
#include <QWidget>

#include <QString>
#include <QLabel>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QMediaPlayer>

#include <QPushButton>
#include <QVideoWidget>

#include <QSlider>
#include <QMediaPlaylist>

QString getTimeStamp(qint64);

class MediaPlayer : public QWidget
{
    Q_OBJECT

    public:
        MediaPlayer(QWidget *parent);

        void setPlaylist(QMediaPlaylist*);

        QSlider *getSlider();
        QMediaPlaylist *getPlaylist();
        QMediaPlayer  *getPlayer();
    private:
        QVBoxLayout *mainLayout;

        QHBoxLayout *secondaryLayout, *primaryLayout;

        QMediaPlayer *playerMain;
        QVideoWidget *playerOutput;

        QPushButton *playButton, *pauseButton;
        QSlider *audioSlider;
        QLabel *timeStamp;

    public slots:
        void updateTimeStamp(qint64);





};

#endif // MEDIAPLAYER_H
