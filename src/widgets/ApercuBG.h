/****************************************************************************
 ** Makou Reactor Final Fantasy VII Field Script Editor
 ** Copyright (C) 2009-2022 Arzel Jérôme <myst6re@gmail.com>
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/
#pragma once

#include <QtWidgets>
#include "core/field/Field.h"

class ApercuBG : public QLabel
{
	Q_OBJECT
public:
	explicit ApercuBG(QWidget *parent = nullptr);
	void fill(Field *field, bool reload = false);
	void clear();
	inline QSize minimumSizeHint() const override {
		return QSize(100, 100);
	}
	inline QSize sizeHint() const override {
		return QSize(300, 225);
	}
signals:
	void clicked();
public slots:
	void drawBackground();
private:
	static QPixmap errorPixmap(const QSize &size);
	Field *_field;
	QPixmap _background;
	QSize _backgroundSize;
	bool _error;
protected:
	void mouseReleaseEvent(QMouseEvent *e) override;
	void resizeEvent(QResizeEvent *e) override;
};
