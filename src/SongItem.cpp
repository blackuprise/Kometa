/*
 * SongItem.cpp
 *
 *  Created on: Jan 18, 2011
 *      Author: miroslav
 */

#include "SongItem.h"

SongItem::SongItem(Song* song) : QStandardItem(song->getTitle())
{
	this->song = song;
}

SongItem::~SongItem() {
}

Song* SongItem::getSong() {
	return song;
}
