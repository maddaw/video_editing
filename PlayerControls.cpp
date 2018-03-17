#include "PlayerControls.h"

CustomPlayerControls::CustomPlayerControls(QMediaPlayer *tempConnectedPlayer, QWidget *parent) : QWidget(parent)
{

    this->setParent(parent);

    connectedPlayer = tempConnectedPlayer;

    controlsMainLayout = new QVBoxLayout;
    controlButtonsLayout = new QHBoxLayout;
    controlBottomLayout = new QHBoxLayout;

    playButton = new QPushButton("PLAY", this);
    playButton->setCursor(Qt::PointingHandCursor);
    playButton->setMaximumWidth(50);

    pauseButton = new QPushButton("PAUSE", this);
    pauseButton->setCursor(Qt::PointingHandCursor);
    pauseButton->setMaximumWidth(50);

    addMediaButton = new QPushButton("ADD", this);
    addMediaButton->setCursor(Qt::PointingHandCursor);
    addMediaButton->setMaximumWidth(50);

    videoSlider = new QSlider(Qt::Horizontal, this); /* Qt::Vertical - Pionowo, Qt::Horizontal - Poziomo */
    videoSlider->setCursor(Qt::OpenHandCursor);
    videoSlider->setMaximumWidth(300);

    audioSlider = new QSlider(Qt::Horizontal, this);
    audioSlider->setCursor(Qt::OpenHandCursor);
    audioSlider->setValue(100);
    audioSlider->setMaximumWidth(100);

    videoDurationLabel = new QLabel("00:00:00/00:00:00", this);

    controlButtonsLayout->addWidget(playButton);
    controlButtonsLayout->addWidget(pauseButton);
    controlButtonsLayout->addWidget(addMediaButton);
    controlButtonsLayout->addWidget(audioSlider);

    controlBottomLayout->addWidget(videoSlider);
    controlBottomLayout->addWidget(videoDurationLabel);

    controlsMainLayout->addLayout(controlButtonsLayout);
    controlsMainLayout->addLayout(controlBottomLayout);


    this->setLayout(controlsMainLayout);
    this->setMaximumWidth(videoSlider->maximumWidth());

    videoDuration = "00:00:00";

    connect(playButton, &QPushButton::released, this, &CustomPlayerControls::playReleased);
    connect(pauseButton, &QPushButton::released, this, &CustomPlayerControls::pauseReleased);
    connect(addMediaButton, &QPushButton::released, this, &CustomPlayerControls::addReleased);

    connect(audioSlider, &QSlider::valueChanged, this, &CustomPlayerControls::volumeChanged);
    connect(videoSlider, &QSlider::sliderMoved, this, &CustomPlayerControls::renderChanged);

    connect(connectedPlayer, &QMediaPlayer::durationChanged, this, &CustomPlayerControls::updateSliderRange);
    connect(connectedPlayer, &QMediaPlayer::positionChanged, this, &CustomPlayerControls::updateSlider);

    connect(connectedPlayer, &QMediaPlayer::positionChanged, this, &CustomPlayerControls::updateTimeLabel);

}

QSlider* CustomPlayerControls::getAudioSlider()
{
    return audioSlider;
}

QSlider* CustomPlayerControls::getVideoSlider()
{
    return videoSlider;
}

void CustomPlayerControls::playReleased()
{
    emit playSignal();
}

void CustomPlayerControls::pauseReleased()
{
    emit pauseSignal();
}

void CustomPlayerControls::addReleased()
{
    emit addMediaSignal();
}

void CustomPlayerControls::volumeChanged()
{
    emit volumeChangedSignal(audioSlider->value());
}

void CustomPlayerControls::renderChanged()
{
    emit renderChangedSignal(videoSlider->value());
}

void CustomPlayerControls::updateSlider(qint64 newValue)
{
    videoSlider->setValue(newValue);
}

void CustomPlayerControls::updateSliderRange(qint64 newValue)
{
    videoSlider->setMaximum(newValue);
    videoDuration = getTimeLabel(newValue/1000);
    videoDurationLabel->setText("00:00:00/" + videoDuration);

}

void CustomPlayerControls::updateTimeLabel(qint64 newValue)
{
    videoDurationLabel->setText(getTimeLabel(newValue/1000) + "/" + videoDuration);
}

/*
 Accepts videoPosition (in seconds) and returns corresponding time label in format: HH:MM:SS
    Przyjmuje aktualną pozycję filmiku (sekundy) i zwraca odpowiadającą etykietę w formacie GG:MM:SS
*/
QString CustomPlayerControls::getTimeLabel(qint64 videoPosition)
{
    QString newText;
    qint64 tempValue;

    tempValue = videoPosition/3600;
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
