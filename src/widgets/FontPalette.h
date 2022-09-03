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
#include <WindowBinFile>

#define CELL_SIZE   16
#define BORDER_SIZE 1

class FontPalette : public QWidget
{
	Q_OBJECT
public:
	explicit FontPalette(QWidget *parent = nullptr);
	virtual ~FontPalette() override;
	void setReadOnly(bool ro);
	void setWindowBinFile(WindowBinFile *windowBinFile);
	void setCurrentPalette(WindowBinFile::FontColor palette);
	QRgb currentColor() const;
public slots:
	void setColor(int id, QRgb color);
	void clear();
	void reset();
signals:
	void colorChanged(int id);
protected:
	virtual QSize sizeHint() const override;
	virtual QSize minimumSizeHint() const override;
	virtual void paintEvent(QPaintEvent *e) override;
	virtual void mousePressEvent(QMouseEvent *e) override;
private:
	void setColorCount(quint8 colorCount);
	void setCurrentColor(int id);
	int getColorId(const QPoint &pos);
	quint8 colorCount;
	int _currentColor;
	WindowBinFile::FontColor _currentPalette;
	QVector<QRgb> palette, copyPalette;
	bool readOnly;
	WindowBinFile *_windowBinFile;
};
