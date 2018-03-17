#include "MediaControls.h"

MediaControls::MediaControls(QWidget *parent = nullptr, QString tempMediaFolder = "")
{
   this->setParent(parent);

   mediaFolder = tempMediaFolder;

   qDebug() << "All media will be stored in: " << mediaFolder;

   mainLayout = new QVBoxLayout(this);

   topLayout = new QHBoxLayout(this);
   bottomLayout = new QHBoxLayout(this);

   addMedia = new QPushButton("ADD",this);
   addMedia->setCursor(Qt::PointingHandCursor);

   removeMedia = new QPushButton("REMOVE", this);
   removeMedia->setCursor(Qt::PointingHandCursor);

   selectMedia = new QPushButton("SELECT", this);
   selectMedia->setCursor(Qt::PointingHandCursor);

   resourcesList = new QListWidget(this);

   topLayout->addWidget(resourcesList);

   bottomLayout->addWidget(addMedia);
   bottomLayout->addWidget(removeMedia);
   bottomLayout->addWidget(selectMedia);

   mainLayout->addLayout(topLayout);
   mainLayout->addLayout(bottomLayout);

   connect(addMedia, &QPushButton::released, this, &MediaControls::addReleased);
   connect(removeMedia, &QPushButton::released, this, &MediaControls::removeReleased);
   connect(selectMedia, &QPushButton::released, this, &MediaControls::selectReleased);

   this->setLayout(mainLayout);

}

void MediaControls::addReleased()
{
    qDebug() << "Media Controls Connection ADD";

    QString selectedVideo = QFileDialog::getOpenFileName(this, "Open a file", "c:\\", nullptr); //(this, tr("Select video"),"c:\\", nullptr);

    resourcesList->addItem(selectedVideo);

    emit addMediaSignal(selectedVideo);
}

void MediaControls::removeReleased()
{
    emit removeMediaSignal(qint16(resourcesList->currentRow())); /* KOLEJNOŚĆ MA ZNACZENIE !!! */

    resourcesList->takeItem(resourcesList->currentRow());
}

void MediaControls::selectReleased()
{
    qDebug() << "Media Controls Connection SELECT";

    emit selectMediaSignal(qint16(resourcesList->currentRow()));
}

void MediaControls::addMediaPublic(QString videoLabel)
{
    resourcesList->addItem(videoLabel);
}

void MediaControls::removeMediaPublic(qint64 itemPos)
{
    resourcesList->takeItem(itemPos);
}
