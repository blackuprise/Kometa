/*
 * MediaPlayer.h
 *
 *  Created on: Dec 27, 2010
 *      Author: miroslav
 */

#ifndef MEDIAPLAYER_H_
#define MEDIAPLAYER_H_


#include <QMessageBox>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QHash>
#include <QListView>
#include <QStringList>
#include <QStringListModel>
#include <QList>
#include <QSystemTrayIcon>

#include <stdlib.h>
#include <irrKlang.h>
#include <id3/tag.h>

#include "Constants.h"
#include "SoundEventReceiver.cpp"
#include "Song.h"

using namespace irrklang;
using namespace std;

class MediaPlayer {
private:
	// Sound engine
	ISoundEngine* soundEngine;
	ISound* currentSound;
	Song* currentSong;
	ISoundStopEventReceiver* soundEventReceiver;

	// Song repository
	QHash<QString, Song*> *songList;
	QList<Song*>* displayList;

	QString getMp3TagFieldById(ID3_Tag mp3Tag, ID3_FrameID frameId);
public:
	MediaPlayer();
	virtual ~MediaPlayer();

	void play(QString filePath);
	void play(Song* song);
	void stop();
	void pause();
	void next();
	void prev();
	QString getCurrentTime();
    float currentSongPercent = 0;
	Song* getCurrentSong();
	void addMediaDir(QString dirPath);
	QList<Song*>* getSongList();
	bool isFinished();

    float getCurrentSongPercent();
    void clearSongList();
};

#endif /* MEDIAPLAYER_H_ */
