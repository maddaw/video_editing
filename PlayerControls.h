#ifndef CUSTOMPLAYERSCONTROLS_H
#define CUSTOMPLAYERSCONTROLS_H


#include <QDebug>

#include <QWidget>
#include <QLabel>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QPushButton>

#include <QMetaDataReaderControl>
#include <QMediaPlayer>

#include <QSlider>

class CustomPlayerControls : public QWidget
{
    Q_OBJECT

    private:
        QMediaPlayer *connectedPlayer;

        QVBoxLayout *controlsMainLayout;
        QHBoxLayout *controlButtonsLayout;
        QHBoxLayout *controlBottomLayout;

        QPushButton *playButton;
        QPushButton *pauseButton;
        QPushButton *addMediaButton;

        QLabel *videoDurationLabel;

        QSlider *videoSlider;
        QSlider *audioSlider;

        QString videoDuration;

    public:
        explicit CustomPlayerControls(QMediaPlayer *tempConnectedPlayer = nullptr, QWidget *parent = nullptr);

        QSlider* getAudioSlider();
        QSlider* getVideoSlider();

        QString getTimeLabel(qint64 videoPositionIndex);
    signals:
        void playSignal();
        void pauseSignal();
        void addMediaSignal();
        void volumeChangedSignal(int volume);
        void renderChangedSignal(int change);

    public slots:
        void addReleased();
        void playReleased();
        void pauseReleased();
        void volumeChanged();
        void renderChanged();
        void updateSlider(qint64);
        void updateSliderRange(qint64);
        void updateTimeLabel(qint64);


        /* POCZYTAC O ACTION MAPPER */
};

#endif // CUSTOMPLAYERSCONTROLS_H
