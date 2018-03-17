#include "MediaPlayer.h"

MediaPlayer::MediaPlayer(QWidget *parent = nullptr)
{
   this->setParent(parent);

   mainLayout = new QVBoxLayout(this);

   primaryLayout = new QHBoxLayout(this);
   secondaryLayout = new QHBoxLayout(this);

   playerMain = new QMediaPlayer(this);
   playerMain->setVolume(100);

   playerOutput = new QVideoWidget(this);
   playerOutput->setMinimumSize(600, 480);

   playerMain->setVideoOutput(playerOutput);

   playButton = new QPushButton("PLAY", this);
   playButton->setCursor(Qt::PointingHandCursor);

   pauseButton = new QPushButton("PAUSE", this);
   pauseButton->setCursor(Qt::PointingHandCursor);

   timeStamp = new QLabel("00:00:00/00:00:00", this);

   audioSlider = new QSlider(Qt::Horizontal, this);
   audioSlider->setCursor(Qt::PointingHandCursor);
   audioSlider->setMaximumWidth(100);
   audioSlider->setMaximum(100);
   audioSlider->setValue(100);

   primaryLayout->addWidget(playerOutput);

   secondaryLayout->addWidget(playButton);
   secondaryLayout->addWidget(pauseButton);
   secondaryLayout->addWidget(timeStamp);
   secondaryLayout->addWidget(audioSlider);

   mainLayout->addLayout(primaryLayout);
   mainLayout->addLayout(secondaryLayout);

   connect(playButton, &QPushButton::released, playerMain, &QMediaPlayer::play);
   connect(pauseButton,&QPushButton::released, playerMain, &QMediaPlayer::pause);



   this->setLayout(mainLayout);
}

void MediaPlayer::setPlaylist(QMediaPlaylist *tempPlaylist = nullptr)
{
    playerMain->setPlaylist(tempPlaylist);
}

void MediaPlayer::updateTimeStamp(qint64 posValue)
{
    QString newTimeStamp = getTimeStamp(posValue/1000) + "/" + getTimeStamp(playerMain->duration()/1000);
    timeStamp->setText(newTimeStamp);
}

QMediaPlayer* MediaPlayer::getPlayer()
{
    return playerMain;
}

QMediaPlaylist* MediaPlayer::getPlaylist()
{
    return playerMain->playlist();
}

QSlider* MediaPlayer::getSlider()
{
    return audioSlider;
}

/* --------FUNKCJA POMOCNICZA-------- */

QString getTimeStamp(qint64 videoPosition)
{


    qint64 tempValue = videoPosition/3600;

    QString newText;

    if(tempValue >= 10)
    {
        newText = newText + QString::number(tempValue) + ":";
    }else
    {
        newText = newText + "0" + QString::number(tempValue) + ":";
    }

    tempValue = (videoPosition - (tempValue * 3600)) / 60;
    if(tempValue >= 10)
    {
        newText = newText + QString::number(tempValue) + ":";
    }else
    {
        newText = newText + "0" + QString::number(tempValue) + ":";
    }

    tempValue = videoPosition % 60;
    if(tempValue >= 10)
    {
        newText = newText + QString::number(tempValue);
    }else
    {
        newText = newText + "0" + QString::number(tempValue);
    }

    return newText;
}

/*-------------------------------------------------------------------------*/
