/*
 * MediaPlayer.cpp
 *
 *  Created on: Dec 27, 2010
 *      Author: miroslav
 */

#include "MediaPlayer.h"

MediaPlayer::MediaPlayer() {
	soundEngine = createIrrKlangDevice();
	if (!soundEngine) {
		qDebug() << "Couldn't initialize irrKlang sound engine.";
	} else {
		qDebug() << "irrKlang sound engine initialized.";
	}
	soundEventReceiver = new SoundEventReceiver();
	songList = new QHash<QString, Song*>();
	displayList = new QList<Song*>();
}

MediaPlayer::~MediaPlayer() {
	soundEngine->drop();
	delete soundEventReceiver;
	delete songList;
	delete displayList;
}

void MediaPlayer::play(QString filePath)
{
	Song* songToPlay = songList->value(filePath);
        play(songToPlay);
}

void MediaPlayer::play(Song* song) {
	if (song == NULL) {
		return;
	}
	if (currentSong == song) {
		currentSound->setIsPaused(!currentSound->getIsPaused());
	} else {
		stop();
		currentSong = song;
		currentSound = soundEngine->play2D(song->getPath().toLatin1().data(),
				false, false, true);
        if (currentSound) {
            currentSound->setSoundStopEventReceiver(soundEventReceiver, this);
        }
	}
}

void MediaPlayer::stop()
{
	soundEngine->stopAllSounds();
}

void MediaPlayer::pause()
{
	currentSound->setIsPaused(true);
}

int MediaPlayer::getCurrentSongPercent()
{
    return currentSongPercent;
}

QString MediaPlayer::getCurrentTime()
{
	ik_u32 position = 0;
	ik_u32 total = 0;
    if (currentSound)
	{
		position = currentSound->getPlayPosition();
		total = currentSound->getPlayLength();
	}
	char currentTime[18];
	int currentSeconds = position / 1000;
	int currentMinute = currentSeconds / 60;
	int currentSecond = currentSeconds % 60;
	int totalSeconds = total / 1000;
	int totalMinute = totalSeconds / 60;
	int totalSecond = totalSeconds % 60;
    currentSongPercent = ((float) currentSeconds) / ((float) totalSeconds) * 100;
	::snprintf(currentTime, 18, "%.2d:%.2d/%.2d:%.2d", currentMinute,
			currentSecond, totalMinute, totalSecond);
    qDebug() << "Percent: " << currentSongPercent;
	return currentTime;
}

//int MediaPlayer::getCurrentPercent() {
//    ik_u32 position = 0;
//    ik_u32 total = 0;
//    if (currentSound)
//    {
//        position = currentSound->getPlayPosition();
//        total = currentSound->getPlayLength();
//        return position / total * 100;
//    } else {
//        return 0;
//    }
//}

Song* MediaPlayer::getCurrentSong()
{
	return currentSong;
}

void MediaPlayer::next()
{
	int currentIndex = displayList->indexOf(currentSong);
	if (currentIndex != displayList->size() - 1)
	{
		play(displayList->at(++currentIndex)->getPath());
	} else {
		currentSong = NULL;
	}
}

QString MediaPlayer::getMp3TagFieldById(ID3_Tag mp3Tag, ID3_FrameID frameId)
{
	ID3_Frame* frame = mp3Tag.Find(frameId);
	return (frame != NULL) ? QString(frame->Field(ID3FN_TEXT).GetRawText()) : "";
}

void MediaPlayer::addMediaDir(QString dirPath)
{
	QDir *dir = new QDir(dirPath);
	QStringList *filters = new QStringList();
    filters->append("*.mp3");
    filters->append("*.flac");
	dir->setNameFilters(*filters);
	QFileInfoList fileList = dir->entryInfoList();
	QString title, artist, genre, album, length;
	for (int i = 0; i < fileList.count(); i++)
	{
		QFileInfo fileInfo = fileList.at(i);
        if (fileInfo.absoluteFilePath().endsWith(".mp3")) {
            ID3_Tag mp3TagInfo;
            mp3TagInfo.Link(fileInfo.absoluteFilePath().toLatin1().data(),
                    ID3TT_ID3V1 | ID3TT_LYRICS3V2 | ID3TT_MUSICMATCH);

            album = getMp3TagFieldById(mp3TagInfo, ID3FID_ALBUM);
            artist = getMp3TagFieldById(mp3TagInfo, ID3FID_LEADARTIST);
            title = getMp3TagFieldById(mp3TagInfo, ID3FID_TITLE);
            length = getMp3TagFieldById(mp3TagInfo, ID3FID_SONGLEN);
            genre = getMp3TagFieldById(mp3TagInfo, ID3FID_CONTENTTYPE);

            Song* song = new Song(artist, title, genre, fileInfo.absoluteFilePath(),
                    album, length.toInt());
            songList->insert(fileInfo.absoluteFilePath(), song);
        } else {
            Song* song = new Song("unkown", fileInfo.fileName() , "", fileInfo.absoluteFilePath(), "", 0);
            songList->insert(fileInfo.absoluteFilePath(), song);
        }

	}
	displayList->clear();
	foreach (Song *song, songList->values())
	{
		displayList->append(song);
	}
	delete filters;
	delete dir;
}

QList<Song*>* MediaPlayer::getSongList()
{
	return displayList;
}

bool MediaPlayer::isFinished()
{
	return currentSound->isFinished();
}
