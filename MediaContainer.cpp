#include "MediaContainer.h"

QString FFMPEGPATH = "C:\\ffmpeg\\bin\\ffmpeg";;

MediaContainer::MediaContainer(QWidget *parent = nullptr)
{
    this->setParent(parent);
    resourcesList = new QMediaPlaylist(this);
}

void MediaContainer::addMedia(QString mediaUrl)
{
     resourcesList->addMedia(QUrl::fromLocalFile(mediaUrl));
}

void MediaContainer::removeMedia(qint16 mediaIndex)
{
    resourcesList->removeMedia(mediaIndex);

    qDebug() << "Media Count: " << resourcesList->mediaCount();

}

void MediaContainer::selectMedia(qint16 mediaIndex)
{
    resourcesList->setCurrentIndex(mediaIndex);
}

void MediaContainer::givePlaylist(QMediaPlayer *playerTemp)
{
    playerTemp->setPlaylist(resourcesList);
}

QMediaPlaylist* MediaContainer::getPlaylist()
{
    return resourcesList;
}

void MediaContainer::cutCurrent(qint64 cutPosition, QString mediaFolder)
{
    if(resourcesList->mediaCount() == 0)
    {
        return;
    }

    bool firstFlag = false, secondFlag = false;

    qDebug() << "CONNECTED CUT SIGNAL";

    cutPosition = (cutPosition/1000);

    QProcess FFMPEG;
    QString inputName, outputName, timeStamp, processName, outputPath;
    QStringList commandList;
    QMessageBox msgBox;

    processName = FFMPEGPATH;

    inputName = QUrl(resourcesList->currentMedia().canonicalUrl().toLocalFile()).toString();


    outputName = resourcesList->currentMedia().canonicalUrl().fileName();

    outputPath = mediaFolder + "/FIRST_" + outputName;

    timeStamp = getTimeLabel(cutPosition);

    commandList << "-ss"
    << "00:00:00"
    << "-i"
    << inputName
    << "-t"
    << timeStamp
    << "-c"
    << "copy"
    << outputPath;

    FFMPEG.start(processName, commandList);

    if ( !(FFMPEG.waitForFinished()) )
    {
       qDebug() << "Cut one failed:" << FFMPEG.errorString();
    }
    else
    {
       qDebug() << "Cut one succeded:" << FFMPEG.readAll();

       resourcesList->addMedia(QUrl::fromLocalFile(outputPath));
       emit mediaOperationSuccess(outputPath);

       firstFlag = true;
    }

    commandList.clear();

    outputPath = mediaFolder + "/SECOND_" + outputName;

    commandList << "-ss"
    << timeStamp
    << "-i"
    << inputName
    << "-c"
    << "copy"
    << outputPath;

    FFMPEG.start(processName, commandList);



    if ( !(FFMPEG.waitForFinished()) )
    {
       qDebug() << "Cut two failed:" << FFMPEG.errorString();
    }
    else
    {
       qDebug() << "Cut two succeded:" << FFMPEG.readAll();

       resourcesList->addMedia(QUrl::fromLocalFile(outputPath));
       emit mediaOperationSuccess(outputPath);

       emit mediaRemoved(resourcesList->currentIndex());
       resourcesList->removeMedia(resourcesList->currentIndex());

       secondFlag = true;
    }

    if(firstFlag && secondFlag)
    {
        msgBox.setText("Video has been succefully cut.");
    }else
    {
        msgBox.setText("There were some errors while cutting the video.");
    }

    msgBox.exec();
}

void MediaContainer::cutAudio(QString mediaFolder)
{
    if(resourcesList->mediaCount() == 0)
    {
        return;
    }

    QProcess FFMPEG;
    QStringList commandList;
    QString inputName, outputName, processName, outputPath;
    QMessageBox msgBox;

    processName = FFMPEGPATH;

    inputName = QUrl(resourcesList->currentMedia().canonicalUrl().toLocalFile()).toString();

    outputName = resourcesList->currentMedia().canonicalUrl().fileName();
    outputPath = mediaFolder + "/NOAUDIO_" + outputName;

    commandList << "-i"
                << inputName
                << "-c"
                << "copy"
                << "-an"
                << outputPath;

    FFMPEG.start(processName, commandList);

    if ( !(FFMPEG.waitForFinished()) )
    {
       qDebug() << "Cutting sound failed:" << FFMPEG.errorString();

       msgBox.setText("There were some errors during the audio removal.");
    }
    else
    {
       qDebug() << "Cutting sound succeded:" << FFMPEG.readAll();
       resourcesList->addMedia(QUrl::fromLocalFile(outputPath));

       msgBox.setText("Audio removal successfull.");

       emit mediaOperationSuccess(outputPath);
    }

    msgBox.show();
}

void MediaContainer::changeSpeed(float speedChanger, QString mediaFolder)
{
    if(resourcesList->mediaCount() == 0)
    {
        return;
    }

    QProcess FFMPEG;
    QStringList commandList;
    QString inputName, outputName, processName, outputPath;

    QMessageBox msgBox;

    processName = FFMPEGPATH;

    inputName = QUrl(resourcesList->currentMedia().canonicalUrl().toLocalFile()).toString();

    outputName = resourcesList->currentMedia().canonicalUrl().fileName();
    outputPath = mediaFolder + "/SPEED_" + QString::number(speedChanger) + "_" + outputName;

    commandList << "-i"
                << inputName
                << "-q"
                << "1"
                << "-vf"
                << "setpts=" + QString::number(1 / speedChanger) + "*PTS"
                << "-filter:a"
                << "atempo=" + QString::number(speedChanger)
                << outputPath;

    FFMPEG.start(processName, commandList);


    if ( !(FFMPEG.waitForFinished()) )

    {
        qDebug() << "Chenging speed failed:" << FFMPEG.errorString();

        msgBox.setText("There were some errors during the speed changing.");
     }

    else

    {
        qDebug() << "Speed has been successfully changed" << FFMPEG.readAll();

        resourcesList->addMedia(QUrl::fromLocalFile(outputPath));

        msgBox.setText("Speed change successfull.");

        emit mediaOperationSuccess(outputPath);
    }

    msgBox.show();
}

/* --------FUNKCJA POMOCNICZA-------- */

QString getTimeLabel(qint64 videoPosition)
{
    qDebug() << videoPosition;

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
