#include "PlaylistView.h"


PlaylistView::PlaylistView(QWidget *parent = nullptr,  CustomMediaPlayer *tempConnectedPlayer = nullptr)
{

    vLayout = new QVBoxLayout(this);
    hLayout = new QHBoxLayout(this);

    this->setParent(parent);

    mediaLabels = new QListWidget(this);

    selectMedia = new QPushButton("SELECT", this);

    deleteMedia = new QPushButton("DELETE", this);


    hLayout->addWidget(selectMedia);
    hLayout->addWidget(deleteMedia);


    this->setLayout(vLayout);

    vLayout->addWidget(mediaLabels);
    vLayout->addLayout(hLayout);

    connectedPlayer = tempConnectedPlayer;

    connect(selectMedia, &QPushButton::released, this, &PlaylistView::selectVideo);
    connect(deleteMedia, &QPushButton::released, this, &PlaylistView::deleteVideo);

}

void PlaylistView::addLabel(QString fileName)
{
    mediaLabels->addItem(fileName);
}

void PlaylistView::selectVideo()
{
    connectedPlayer->getPlaylist()->setCurrentIndex(mediaLabels->currentRow());
    connectedPlayer->getPlayer()->play();
}

void PlaylistView::deleteVideo()
{

    connectedPlayer->getPlaylist()->removeMedia(mediaLabels->currentRow());
    mediaLabels->takeItem(mediaLabels->currentRow());

}
