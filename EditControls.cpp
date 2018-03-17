#include "EditControls.h"

EditControls::EditControls(QWidget *parent = nullptr)
{
    this->setParent(parent);

    mainLayout = new QVBoxLayout(this);

    topLayout = new QHBoxLayout(this);
    bottomLayout = new QHBoxLayout(this);

    cutMedia = new QPushButton("ADD", this);
    cutMedia->setCursor(Qt::PointingHandCursor);

    mediaList = new QListWidget(this);

    videoSlider = new QSlider(this);

    topLayout->addWidget(mediaList);

    bottomLayout->addWidget(cutMedia);

    mainLayout->addWidget(videoSlider);
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);

    this->setLayout(mainLayout);
}
