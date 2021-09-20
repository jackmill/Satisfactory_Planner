/**
 * @file BasicItemButton.cpp
 * Created by jackm on 9/19/2021
 */

#include <QFile>

#include "BasicItemButton.h"

namespace ui {

BasicItemButton::BasicItemButton(QString display_name, QWidget *parent) :
	item_name_(std::move(display_name)),
	QPushButton(parent) {
	
	auto button_size = new QSize(45, 45);
	setFixedSize(*button_size);
	
	setIcon(itemIconFromDisplayName(item_name_));
	setIconSize(*button_size * 0.8);
	
	setToolTip(item_name_);
}

QIcon BasicItemButton::itemIconFromDisplayName(const QString &display_name) {
	QString icon_string = display_name;
	icon_string.replace(' ', '_');
	icon_string.prepend("resources/icon/");
	icon_string.append(".png");
	
	if (QFile(icon_string).exists()) {
		return QIcon(icon_string);
	} else {
		return QIcon("resources/icon/No_Image_Available.png");
	}
}

}