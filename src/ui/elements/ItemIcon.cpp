/**
 * @project Satisfactory_Planner
 * @file ItemIcon.cpp
 *
 * @author Jackson Miller
 * @date 2021-09-18
 * @copyright (c) 2021 Jackson Miller
 */

#include <QFile>
#include <cmath>

#include "ItemIcon.h"
#include "../util.h"

namespace ui {

ItemIcon::ItemIcon(data::Item &item, QWidget *parent) :
	btn_item_(item),
	QPushButton(parent) {
	
	// Button Size
	auto button_size_ = new QSize(45, 45);
	setFixedSize(*button_size_);
	
	// Layout
	layout_ = new QVBoxLayout(this);
	layout_->setMargin(button_size_->width() / 15);
	layout_->addSpacerItem(new QSpacerItem(button_size_->width(), button_size_->height()));
	
	// Icon
	setIcon(util::itemIconFromDisplayName(QString::fromStdString(btn_item_.name())));
	setIconSize(*button_size_ * 0.8);
	
	// Count Label
	item_count_label_ = new QLabel(util::formatItemNumber(btn_item_.amount()), this);
	QFont count_font = QFont(item_count_label_->font());
	count_font.setPixelSize(button_size_->height() / 4);
	item_count_label_->setFont(count_font);
    item_count_label_->setAlignment(Qt::AlignRight);
    item_count_label_->setStyleSheet("font: bold; color: white; background-color: #E59344; border-radius: 3px; margin-right: 1px; margin-left: 1px");
	
	layout_->addWidget(item_count_label_, Qt::AlignRight, Qt::AlignRight);
	
	// Tooltip
	setToolTip(QString::fromStdString(btn_item_.name()) + ": " + QString::number(btn_item_.amount()));

}

void ItemIcon::updateItemCount(const int &count) {
	btn_item_.setAmount(count);
	item_count_label_->setText(util::formatItemNumber(btn_item_.amount()));
	setToolTip(QString::fromStdString(btn_item_.name()) + ": " + QString::number(count));
}

void ItemIcon::setLabelCount(const int count) {
    item_count_label_->setText(util::formatItemNumber(count));
    setToolTip(QString::fromStdString(btn_item_.name()) + ": " + QString::number(count));
}

void ItemIcon::setCleared() {
    setStyleSheet("background-color: #00FF00;");
}

} // namespace ui