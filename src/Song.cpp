/*
 * Song.cpp
 *
 *  Created on: Dec 29, 2010
 *      Author: miroslav
 */

#include "Song.h"

Song::Song(QString artist, QString title, QString genre, QString path,
		QString album, int length) {
	this->artist = artist;
	this->album = album;
	this->title = title;
	this->genre = genre;
	this->length = length;
	this->path = path;
}

Song::~Song() {
}

QString Song::getArtist()
{
	return artist;
}

QString Song::getAlbum()
{
	return album;
}

QString Song::getTitle()
{
	return title;
}

QString Song::getGenre()
{
	return genre;
}

QString Song::getPath()
{
	return path;
}

int Song::getLength()
{
	return length;
}
