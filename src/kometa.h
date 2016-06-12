#ifndef KOMETA_H
#define KOMETA_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QTimer>
#include <QSettings>
#include <QStandardItemModel>

#include "MediaPlayer.h"
#include "SongItem.h"
#include "ui_kometa.h"
#include "Song.h"

class Kometa : public QMainWindow
{
    Q_OBJECT

public:
    Kometa(QWidget *parent = 0);
    ~Kometa();
    void addSongListItems(const QList<Song*>* songList);
    QStandardItemModel* getSongViewModel();
    QImage* PLAY_IMAGE;
    QImage* PLAY_IMAGE_INVERTED;

public slots:
    void play();
    void playSelected();
    void next();
    void updateSongInfo();
    void addMedia();
    void showSongBalloon(Song* song);
    MediaPlayer* getMediaPlayer();

private:
    Ui::KometaClass ui;
    QSettings* settings;
    MediaPlayer* mediaPlayer;
    QTimer* timer;
    QStandardItemModel* songItemModel;
    QSystemTrayIcon* trayIcon;
};

#endif // KOMETA_H
