/*
 * SongItem.h
 *
 *  Created on: Jan 18, 2011
 *      Author: miroslav
 */
#include <QStandardItem>

#include "Song.h"

#ifndef SONGITEM_H_
#define SONGITEM_H_

class SongItem : public QStandardItem {
public:
	SongItem(Song* song);
	virtual ~SongItem();
	Song* getSong();
private:
	Song* song;
};

#endif /* SONGITEM_H_ */
