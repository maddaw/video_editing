#include "MainWindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("QtPlayerTemplate");

    mainLayout = new QVBoxLayout(this);

    topLayout = new QHBoxLayout();
    middleLayout = new QHBoxLayout();
    bottomLayout = new QHBoxLayout();

    completePlayer = new CustomMediaPlayer(centralWidget());

    playlistView = new PlaylistView(centralWidget(), completePlayer);

    topLayout->addWidget(playlistView);
    topLayout->addWidget(completePlayer);

    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(middleLayout);
    mainLayout->addLayout(bottomLayout);

    this->centralWidget()->setLayout(mainLayout);

    connect(completePlayer, &CustomMediaPlayer::mediaAdded, playlistView, &PlaylistView::addLabel);

    setDefaultSize();




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setDefaultSize()
{
    QSize availableSize;
    this->move(qApp->desktop()->availableGeometry().width() / 2, qApp->desktop()->availableGeometry().height() / 2);

    availableSize.setWidth( availableSize.width() * 0.6);
    availableSize.setHeight( availableSize.height() * 0.6);

    this->resize(availableSize);

}
