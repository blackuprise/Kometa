#include "kometa.h"
#include "MediaPlayer.h"
#include "SongViewDelegate.h"

Kometa::Kometa(QWidget *parent)
    : QMainWindow(parent)
{
	ui.setupUi(this);

	mediaPlayer = new MediaPlayer();

	songItemModel = new  QStandardItemModel();
	ui.lvSongs->setItemDelegate(new SongViewDelegate(this));
	ui.lvSongs->setModel(songItemModel);
	ui.lvSongs->setSelectionMode(QAbstractItemView::SingleSelection);

	trayIcon = new QSystemTrayIcon(this);
	trayIcon->setIcon(QIcon(QString::fromUtf8(":/images/images/media-skip-backward.png")));
	trayIcon->setToolTip("Kometa");
	trayIcon->show();
	trayIcon->showMessage(tr("Kometa's wanda"), tr("Welcome to Kometa, enjoy!"), QSystemTrayIcon::Information, 5000);

	timer = new QTimer(this);
	timer->setInterval(100);

	QCoreApplication::setOrganizationName("Low Quality Software");
	QCoreApplication::setOrganizationDomain("");
	QCoreApplication::setApplicationName("Kometa");

	settings = new QSettings();
	restoreGeometry(settings->value("window/geometry").toByteArray());
	restoreState(settings->value("window/state").toByteArray());
    if (settings->contains("bookmarks")) {
        //mediaPlayer->setBookmarks(settings->value("application/bookmarks"));
    }

	// Setup Icons.
	PLAY_IMAGE = new QImage(QString::fromUtf8(":/images/images/audio-volume-medium.png"));
	PLAY_IMAGE_INVERTED = new QImage(QString::fromUtf8(":/images/images/audio-volume-medium-inverted.png"));

	connect(ui.btPlay, SIGNAL(clicked()), this, SLOT(playSelected()));
	connect(ui.btNext, SIGNAL(clicked()), this, SLOT(next()));
	connect(ui.actionAdd_media, SIGNAL(triggered()), this, SLOT(addMedia()));
	connect(ui.lvSongs, SIGNAL(doubleclicked()), this, SLOT(playSelected()));
    connect(ui.btClear, SIGNAL(clicked()), this, SLOT(clearList()));
    connect(ui.btBookmark, SIGNAL(clicked()), this, SLOT(addToBookmark()));
	connect(timer, SIGNAL(timeout()), this, SLOT(updateSongInfo()));
}

Kometa::~Kometa()
{
	settings->beginGroup("window");
	settings->setValue("geometry", saveGeometry());
	settings->setValue("state", saveState());
	settings->endGroup();
    settings->beginGroup("application");
    //settings->setValue("bookmarks", NULL);
    settings->endGroup();

	mediaPlayer->stop();
	timer->stop();
	delete PLAY_IMAGE;
	delete PLAY_IMAGE_INVERTED;
	delete mediaPlayer;
	delete timer;
	delete settings;
}

void Kometa::play()
{
	playSelected();
}

void Kometa::playSelected()
{
    if (!ui.lvSongs->model()->hasChildren()) {
        return;
    }
	QModelIndexList selected = ui.lvSongs->selectionModel()->selectedIndexes();
    Song* songToPlay = NULL;
    if (!selected.isEmpty()) {
        songToPlay = static_cast<SongItem*>(songItemModel->itemFromIndex(selected[0]))->getSong();
    } else {
        songToPlay = static_cast<SongItem*>(songItemModel->item(0, 0))->getSong();
    }

	mediaPlayer->play(songToPlay);
    qDebug() << tr("Playing: ") << songToPlay->getArtist() << " " << songToPlay->getTitle();
	timer->start();
	showSongBalloon(mediaPlayer->getCurrentSong());
	// Ugly fix to draw play icon, should be moved to model to draw this icon?
    ui.lvSongs->repaint();
}

void Kometa::next()
{
	mediaPlayer->next();
	showSongBalloon(mediaPlayer->getCurrentSong());
	// Ugly fix to draw play icon, should be moved to model to draw this icon?
	ui.lvSongs->repaint();
}

void Kometa::updateSongInfo()
{
	ui.lbTime->setText(mediaPlayer->getCurrentTime());
	Song* song = mediaPlayer->getCurrentSong();
	ui.lbSongTitle->setText(song->getTitle());
	ui.lbSongArtist->setText(song->getArtist());
	ui.lbSongAlbum->setText(song->getAlbum());
	if (mediaPlayer->isFinished())
	{
		mediaPlayer->next();
	}
    ui.lvSongs->repaint();
}

void Kometa::addMedia()
{
	QString dirPath = QFileDialog::getExistingDirectory(this, tr("Add media"), "", QFileDialog::QFileDialog::ShowDirsOnly);
	mediaPlayer->addMediaDir(dirPath);
	addSongListItems(mediaPlayer->getSongList());
}

void Kometa::addSongListItems(const QList<Song*>* songList)
{
	foreach(Song* song, *songList) {
		SongItem* songItem = new SongItem(song);
		songItemModel->invisibleRootItem()->appendRow(songItem);
	}
}

QStandardItemModel* Kometa::getSongViewModel()
{
	return songItemModel;
}

void Kometa::showSongBalloon(Song* song)
{
    if (song != NULL) {
        trayIcon->showMessage(tr("Playing..."), song->getArtist() + " - "
                + song->getTitle(), QSystemTrayIcon::Information, 4000);
    }
}

MediaPlayer* Kometa::getMediaPlayer()
{
	return mediaPlayer;
}
void Kometa::addToBookmark() {
   mediaPlayer->addToBookmarks(mediaPlayer->getCurrentDir());
}

void Kometa::clearList()
{
    mediaPlayer->clearSongList();
    songItemModel->clear();
    mediaPlayer->stop();
}

void Kometa::on_btPlay_clicked()
{

}
