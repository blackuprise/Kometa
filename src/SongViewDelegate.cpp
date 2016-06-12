/*
 * SongViewDelegate.cpp
 *
 *  Created on: Jan 17, 2011
 *      Author: miroslav
 */

#include "SongViewDelegate.h"

SongViewDelegate::~SongViewDelegate(){

}
void SongViewDelegate::paint(QPainter* painter, const QStyleOptionViewItem &option,const QModelIndex &index) const {
	Kometa* kometaWidget = static_cast<Kometa*>(parent());
	SongItem* songItem =
		static_cast<SongItem*>(kometaWidget->getSongViewModel()->itemFromIndex(index));
	Song* song = songItem->getSong();
	painter->save();
	QImage *playImage = kometaWidget->PLAY_IMAGE;
	if (option.state & QStyle::State_Selected) {
		painter->fillRect(option.rect, option.palette.highlight());
		painter->setBrush(option.palette.highlight());
		QPen pen(QColor::fromRgb(255, 255, 255, 255));
		painter->setPen(pen);
    }
	QFont mainFont = QApplication::font();
	mainFont.setBold(true);
	painter->setFont(mainFont);
	painter->drawText(QPoint(option.rect.left() + 5, option.rect.top()
			+ option.fontMetrics.height()), song->getTitle());
	QFont minorFont = QApplication::font();
	minorFont.setPixelSize(minorFont.pixelSize() - 3);
	painter->setFont(minorFont);
	QString lowerInfo("by " + song->getArtist());
    painter->drawText(QPoint(option.rect.left() + 5, (int)option.rect.top() + 2
			* option.fontMetrics.height()), lowerInfo);
	// Draw play media icon.
	if (kometaWidget->getMediaPlayer()->getCurrentSong() == song) {
		painter->drawImage(QPoint(option.rect.right() - 32,
				(int) option.rect.top() + (option.rect.height() - playImage->height()) / 2), *playImage);
        // Draw line for song progress.
        int total = option.rect.right() - option.rect.left() - 10;
        int currentBar = ((float) total * kometaWidget->getMediaPlayer()->getCurrentSongPercent()) / 100;
        int top = (int)option.rect.top() + 2.5 * option.fontMetrics.height();
        painter->setBrush(QBrush(QColor(77, 31, 115)));
        painter->drawRect(QRect(QPoint(option.rect.left() + 5, top),
                                QPoint(option.rect.left() + 5 + currentBar, top + 2)));
	}

	painter->restore();
}

QSize SongViewDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
	SongItem* songItem =
		static_cast<SongItem*> (static_cast<Kometa*> (parent())->getSongViewModel()->itemFromIndex(index));
	return QSize(option.fontMetrics.width(songItem->getSong()->getTitle()), option.fontMetrics.height() * 3);
}

QWidget* SongViewDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
    		const QModelIndex &index) const {
	return NULL;
}
