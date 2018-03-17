#ifndef EDITORCONTROLS_H
#define EDITORCONTROLS_H

#include <QWidget>

#include <QMediaPlaylist>

#include <QListWidget>
#include <QList>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QDebug>

#include <QPushButton>
#include <QSlider>

#include <QProcess>
#include <QStringList>
#include <QString>

#include <QMessageBox>
#include <QInputDialog>

class EditorControls : public QWidget
{
    Q_OBJECT

    public:
        EditorControls(QWidget *parent, QString tempMediaFolder);

        QSlider* getSlider();
    private:
        QString mediaFolder;

        QVBoxLayout *mainLayout;

        QHBoxLayout *topLayout;
        QHBoxLayout *bottomLayout;

        QPushButton *cutMedia, *removeSound, *changeSpeed;

        QSlider *videoSlider;

    protected slots:
        void cutReleased();
        void changeSpeedReleased();
        void removeAudioReleased();

    signals:
        void cutMediaSignal(qint64, QString);
        void changeSpeedSignal(float, QString);
        void removeAudioSignal(QString);

};

#endif // EDITORCONTROLS_H
