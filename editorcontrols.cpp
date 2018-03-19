#include "EditorControls.h"

/* DODAC ZMIENNA ODPOWIADAJACA ZA DLUGOSC VIDEO (OSZCZEDNOSC MOCY) */

EditorControls::EditorControls(QWidget *parent = nullptr, QString tempMediaFolder = "")
{
    this->setParent(parent);

    mediaFolder = tempMediaFolder;

    mainLayout = new QVBoxLayout(this);

    topLayout = new QHBoxLayout(this);
    bottomLayout = new QHBoxLayout(this);

    cutMedia = new QPushButton("CUT", this);
    cutMedia->setCursor(Qt::PointingHandCursor);

    changeSpeed = new QPushButton("CHANGE SPEED", this);
    changeSpeed->setCursor(Qt::PointingHandCursor);

    removeSound = new QPushButton("REMOVE AUDIO", this);
    removeSound->setCursor(Qt::PointingHandCursor);

    videoSlider = new QSlider(Qt::Horizontal, this);
    videoSlider->setCursor(Qt::PointingHandCursor);


    bottomLayout->addWidget(cutMedia);
    bottomLayout->addWidget(removeSound);
    bottomLayout->addWidget(changeSpeed);

    mainLayout->addWidget(videoSlider);
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);

    connect(cutMedia, &QPushButton::released, this, &EditorControls::cutReleased);
    connect(changeSpeed, &QPushButton::released, this, &EditorControls::changeSpeedReleased);
    connect(removeSound, &QPushButton::released, this, &EditorControls::removeAudioReleased);

    this->setLayout(mainLayout);


}

QSlider* EditorControls::getSlider()
{
    return videoSlider;
}

void EditorControls::cutReleased()
{    
    QMessageBox msgBox;
    msgBox.setText("Proceed ?");
    msgBox.setInformativeText("Current video will be cut at the chosen position.");
    msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);

    if(msgBox.exec() == QMessageBox::Ok)
    {
        emit cutMediaSignal(videoSlider->value(), mediaFolder);
    }

}

void EditorControls::removeAudioReleased()
{
    QMessageBox msgBox;
    msgBox.setText("Proceed ?");
    msgBox.setInformativeText("Program will cut out the audio from current media.");
    msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);

    if(msgBox.exec() == QMessageBox::Ok)
    {
        emit removeAudioSignal(mediaFolder);
    }
}

void EditorControls::changeSpeedReleased()
{
    QMessageBox msgBox;
    msgBox.setText("Proceed ?");
    msgBox.setInformativeText("Speed will be changed (you will choose variables later).");
    msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);

    if(msgBox.exec() == QMessageBox::Ok)
    {

        QStringList speedVariables;
        speedVariables << tr("0.5") << tr("0.75") << tr("1.5") <<tr("1.75")  << tr("2.0");

        bool execFlag;
        QString userChoice = QInputDialog::getItem(this, tr("QInputDialog::getItem()"), tr("Desired Speed:"), speedVariables, 0, false, &execFlag);
        if (execFlag && !userChoice.isEmpty())
        {
            emit changeSpeedSignal(userChoice.toFloat(), mediaFolder);
        }
    }
}
