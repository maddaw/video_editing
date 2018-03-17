#ifndef MEDIACONTAINER_H
#define MEDIACONTAINER_H

#include <QWidget>

#include <QList>
#include <QString>
#include <QStringList>
#include <QMediaPlaylist>
#include <QMediaPlayer>

#include <QDebug>

#include <QUrl>
#include <QProcess>

#include <QMessageBox>

QString getTimeLabel(qint64 videoPosition);

class MediaContainer : public QObject
{
    Q_OBJECT

    public:
        MediaContainer(QWidget *parent);
        QMediaPlaylist *getPlaylist();

    private:
        QMediaPlaylist *resourcesList;

    signals:
        void mediaRemoved(qint64);
        void mediaOperationSuccess(QString);

    public slots:
        void addMedia(QString);
        void removeMedia(qint16);
        void selectMedia(qint16);

        void givePlaylist(QMediaPlayer*);
        void cutCurrent(qint64, QString);
        void cutAudio(QString);
        void changeSpeed(float, QString);

};

#endif // MEDIACONTAINER_H
