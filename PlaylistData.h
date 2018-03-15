#ifndef CUSTOMPLAYLISTDATA_H
#define CUSTOMPLAYLISTDATA_H

#include <QAbstractItemModel>
#include <QListView>
#include <QFileInfo>
#include <QUrl>
#include <QMediaPlaylist>

class customPlaylistData : public QAbstractItemModel
{

    private:
        QMediaPlaylist *mediaPlaylist;
        QListView *playlistView;
    public:
        void setPlaylist(QMediaPlaylist*);

        customPlaylistData();
};

#endif // CUSTOMPLAYLISTDATA_H
