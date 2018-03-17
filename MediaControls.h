#ifndef EDITCONTROLS_H
#define EDITCONTROLS_H

#include <QWidget>
#include <QObject>

#include <QMediaPlaylist>

#include <QListWidget>
#include <QList>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QDebug>

#include <QPushButton>

#include <QFileDialog>
#include <QFile>

#include <QSlider>

#include <QProcess>
#include <QStringList>
#include <QString>

class MediaControls : public QWidget
{
    Q_OBJECT

    public:
        MediaControls(QWidget *parent, QString tempMediaFolder);



    private:
        QString mediaFolder;

        QVBoxLayout *mainLayout;

        QHBoxLayout *topLayout;
        QHBoxLayout *bottomLayout;

        QPushButton *addMedia, *removeMedia, *selectMedia;

        QListWidget *resourcesList;


    protected slots:
        void addReleased();
        void removeReleased();
        void selectReleased();

    public slots:
        void addMediaPublic(QString);
        void removeMediaPublic(qint64);


    signals:
        void addMediaSignal(QString);
        void removeMediaSignal(qint16);
        void selectMediaSignal(qint16);


};

#endif // EDITCONTROLS_H
