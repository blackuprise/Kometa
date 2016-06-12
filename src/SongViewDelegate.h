/*
 * SongViewDelegate.h
 *
 *  Created on: Jan 17, 2011
 *      Author: miroslav
 */

#ifndef SONGVIEWDELEGATE_H_
#define SONGVIEWDELEGATE_H_

#include <Qt>
#include <QApplication>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QTextOption>

#include "kometa.h"

class SongViewDelegate : public QStyledItemDelegate {
	Q_OBJECT
public:

	inline SongViewDelegate(QObject *parent) : QStyledItemDelegate(parent) {}
	virtual ~SongViewDelegate();
	void paint(QPainter* painter, const QStyleOptionViewItem &option,const QModelIndex &index) const;
	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option,
    		const QModelIndex &index) const;
};

#endif /* SONGVIEWDELEGATE_H_ */
