/****************************************************************************
 ** Makou Reactor Final Fantasy VII Field Script Editor
 ** Copyright (C) 2009-2024 Arzel Jérôme <myst6re@gmail.com>
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
#include "ExportChunksDialog.h"
#include "core/Config.h"

ExportChunksDialog::ExportChunksDialog(QWidget *parent) :
	QDialog(parent, Qt::Dialog | Qt::WindowCloseButtonHint)
{
	setWindowTitle(tr("Export to chunks"));

	QGroupBox *group = new QGroupBox(tr("Export"));
	scripts = new QCheckBox(tr("Chunk 1: Scripts/Texts"));
	ca = new QCheckBox(tr("Chunk 2: Camera"));
	id = new QCheckBox(tr("Chunk 5: Walkmesh"));
	tiles = new QCheckBox(tr("Chunk 6: Tiles (unused)"));
	encounter = new QCheckBox(tr("Chunk 7: Encounters"));
	inf = new QCheckBox(tr("Chunk 8: Triggers/gateways"));
	model = new QCheckBox(tr("Chunk 3: Model loader (PC only)"));
	mim = new QCheckBox(tr("Chunk 9: Background (PC only)"));
	palette = new QCheckBox(tr("Chunk 4: Palette (PC only)"));
	
	scripts->setChecked(Config::value("exportChunksCheckedScripts", true).toBool());
	ca->setChecked(Config::value("exportChunksCheckedCa", true).toBool());
	id->setChecked(Config::value("exportChunksCheckedId", true).toBool());
	tiles->setChecked(Config::value("exportChunksCheckedTiles", true).toBool());
	encounter->setChecked(Config::value("exportChunksCheckedEncounter", true).toBool());
	inf->setChecked(Config::value("exportChunksCheckedInf", true).toBool());
	model->setChecked(Config::value("exportChunksCheckedModel", true).toBool());
	mim->setChecked(Config::value("exportChunksCheckedMim", true).toBool());
	palette->setChecked(Config::value("exportChunksCheckedPalette", true).toBool());

	QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal);

	QVBoxLayout *layout = new QVBoxLayout(group);
	layout->addWidget(scripts);
	layout->addWidget(ca);
	layout->addWidget(model);
	layout->addWidget(palette);
	layout->addWidget(id);
	layout->addWidget(tiles);
	layout->addWidget(encounter);
	layout->addWidget(inf);
	layout->addWidget(mim);
	layout->addStretch();

	layout = new QVBoxLayout(this);
	layout->addWidget(group);
	layout->addWidget(buttonBox);
	layout->addStretch();

	connect(buttonBox, &QDialogButtonBox::accepted, this, &ExportChunksDialog::accept);
	connect(buttonBox, &QDialogButtonBox::rejected, this, &ExportChunksDialog::reject);
}

Field::FieldSections ExportChunksDialog::parts() const
{
	Field::FieldSections parts;

	if (scripts->isChecked())   parts |= Field::Scripts;
	if (ca->isChecked())        parts |= Field::Camera;
	if (model->isChecked())     parts |= Field::ModelLoader;
	if (palette->isChecked())   parts |= Field::PalettePC;
	if (id->isChecked())        parts |= Field::Walkmesh;
	if (tiles->isChecked())     parts |= Field::Tiles;
	if (encounter->isChecked()) parts |= Field::Encounter;
	if (inf->isChecked())       parts |= Field::Inf;
	if (mim->isChecked())       parts |= Field::Background;

	Config::setValue("exportChunksCheckedScripts", scripts->isChecked());
	Config::setValue("exportChunksCheckedCa", ca->isChecked());
	Config::setValue("exportChunksCheckedModel", model->isChecked());
	Config::setValue("exportChunksCheckedPalette", palette->isChecked());
	Config::setValue("exportChunksCheckedId", id->isChecked());
	Config::setValue("exportChunksCheckedTiles", tiles->isChecked());
	Config::setValue("exportChunksCheckedEncounter", encounter->isChecked());
	Config::setValue("exportChunksCheckedInf", inf->isChecked());
	Config::setValue("exportChunksCheckedMim", mim->isChecked());

	return parts;
}
