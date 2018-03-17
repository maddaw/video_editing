#include "MainWindow.h"
#include "ui_mainwindow.h"

/* PRZERZUCIC AUDIO SLIDER DO CONTROLEK */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("MyEditor");

    mediaFolder = "Temp";
    QDir().mkdir(mediaFolder);

    mediaFolder = QDir().absoluteFilePath(mediaFolder);

    mainLayout = new QVBoxLayout(this);

    topLayout = new QHBoxLayout(this);
    middleLayout = new QHBoxLayout(this);
    bottomLayout = new QHBoxLayout(this);

    mediaContainer = new MediaContainer(this);
    mediaControls = new MediaControls(this, mediaFolder);
    mediaPlayer = new MediaPlayer(this);

    mediaPlayer->setPlaylist(mediaContainer->getPlaylist());

    editControls = new EditorControls(this, mediaFolder);

    topLayout->addWidget(mediaPlayer);
    topLayout->addWidget(mediaControls);

    middleLayout->addWidget(editControls);

    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(middleLayout);
    mainLayout->addLayout(bottomLayout);

    connect(mediaControls, &MediaControls::addMediaSignal, mediaContainer, &MediaContainer::addMedia);
    connect(mediaControls, &MediaControls::removeMediaSignal, mediaContainer, &MediaContainer::removeMedia);
    connect(mediaControls, &MediaControls::selectMediaSignal, mediaContainer, &MediaContainer::selectMedia);

    connect(mediaPlayer->getPlayer(), &QMediaPlayer::positionChanged, editControls->getSlider(), &QSlider::setValue);
    connect(mediaPlayer->getPlayer(), &QMediaPlayer::positionChanged, mediaPlayer, &MediaPlayer::updateTimeStamp);

    connect(mediaPlayer->getPlayer(), &QMediaPlayer::durationChanged, editControls->getSlider(), &QSlider::setMaximum);
    connect(mediaPlayer->getPlayer(), &QMediaPlayer::durationChanged, mediaPlayer, &MediaPlayer::updateTimeStamp);

    connect(mediaPlayer->getSlider(), &QSlider::sliderMoved, mediaPlayer->getPlayer(), &QMediaPlayer::setVolume);

    connect(editControls->getSlider(), &QSlider::sliderMoved, mediaPlayer->getPlayer(), &QMediaPlayer::setPosition);

    connect(editControls, SIGNAL(cutMediaSignal(qint64, QString)), mediaContainer, SLOT(cutCurrent(qint64, QString)) );
    connect(editControls, SIGNAL(changeSpeedSignal(float,QString)), mediaContainer, SLOT(changeSpeed(float,QString)) );

    connect(editControls, &EditorControls::removeAudioSignal, mediaContainer, &MediaContainer::cutAudio);

    connect(mediaContainer, &MediaContainer::mediaOperationSuccess, mediaControls, &MediaControls::addMediaPublic);
    connect(mediaContainer, &MediaContainer::mediaRemoved, mediaControls, &MediaControls::removeMediaPublic);

    this->centralWidget()->setLayout(mainLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
