/*
 * Song.h
 *
 *  Created on: Dec 29, 2010
 *      Author: miroslav
 */

#ifndef SONG_H_
#define SONG_H_

#include <QString>

class Song {
private:
	QString artist;
	QString title;
	QString genre;
	QString path;
	QString album;
	int length;
public:
	Song(QString artist, QString title, QString genre, QString path,
			QString album, int length);
	virtual ~Song();
	QString getArtist();
	QString getAlbum();
	QString getTitle();
	QString getGenre();
	QString getPath();
	int getLength();
};

#endif /* SONG_H_ */
