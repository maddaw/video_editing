#include "MediaPlayer.h"


CustomMediaPlayer::CustomMediaPlayer(QWidget *parent) : QWidget(parent)
{

    this->setParent(parent);

    playerMainLayout = new QVBoxLayout(this);

    playerMain = new QMediaPlayer(this);
    playlistMain = new QMediaPlaylist(this);
    playlistMain->setCurrentIndex(-1);
    playerMain->setPlaylist(playlistMain);



    outputHolder = new QFrame(this);
    outputHolder->setMinimumSize(480, 360);
    outputHolder->setFrameStyle(QFrame::Plain);
    outputHolder->setFrameShape(QFrame::WinPanel);

    playerOutput = new QVideoWidget(outputHolder);
    playerOutput->setMinimumSize(outputHolder->size());

    playerOutput->setAspectRatioMode(Qt::KeepAspectRatio);

    playerMain->setVideoOutput(playerOutput);


    playerControls = new CustomPlayerControls(playerMain, this);

    playerMainLayout->addWidget(outputHolder);
    playerMainLayout->addWidget(playerControls);

    this->setLayout(playerMainLayout);


    connect(playerControls, &CustomPlayerControls::playSignal, playerMain, &QMediaPlayer::play);
    connect(playerControls, &CustomPlayerControls::pauseSignal, playerMain, &QMediaPlayer::pause);
    connect(playerControls, &CustomPlayerControls::addMediaSignal, this, &CustomMediaPlayer::addMedia);

    connect(playerControls, &CustomPlayerControls::volumeChangedSignal, playerMain, &QMediaPlayer::setVolume);
    connect(playerControls, &CustomPlayerControls::renderChangedSignal, playerMain, &QMediaPlayer::setPosition);


   /* POŁĄCZYĆ SIGNALS Z CONTROLOW DO SLOTOW Z PLAYER'A */

}

QMediaPlaylist* CustomMediaPlayer::getPlaylist()
{
    return playlistMain;
}

QMediaPlayer* CustomMediaPlayer::getPlayer()
{
    return  playerMain;
}

CustomPlayerControls* CustomMediaPlayer::getControls()
{
    return playerControls;
}

void CustomMediaPlayer::addMedia()
{
    qDebug() << "Connection Succeded";

    QString selectedVideo = QFileDialog::getOpenFileName(this, tr("Select video"),"c:\\", nullptr);

    playlistMain->addMedia(QUrl::fromLocalFile(selectedVideo));

    emit mediaAdded(selectedVideo);
}
