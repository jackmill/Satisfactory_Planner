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

ItemIcon::ItemIcon(std::shared_ptr<data::Item> item, QWidget *parent) :
	btn_item_(std::move(item)),
	QPushButton(parent) {
	
	// Button Size
	setFixedSize(kSize_);
	
	// Layout
	layout_ = new QVBoxLayout(this);
	layout_->setSpacing(kSize_.width() / 15);
	layout_->addSpacerItem(new QSpacerItem(kSize_.width(), kSize_.height()));
	
	// Icon
	setIcon(util::itemIconFromDisplayName(QString::fromStdString(btn_item_->name())));
	setIconSize(kSize_ * 0.9);
	
	// Count Label
	item_count_label_ = new QLabel(util::formatItemNumber(btn_item_->rate()), this);
	QFont count_font = QFont(item_count_label_->font());
	count_font.setPixelSize(kSize_.height() / 3);
	item_count_label_->setFont(count_font);
    item_count_label_->setAlignment(Qt::AlignRight);
    item_count_label_->setStyleSheet("font: bold; color: white; background-color: #E59344; border-radius: 3px; margin-right: 1px; margin-left: 1px");
	
	layout_->addWidget(item_count_label_, Qt::AlignRight, Qt::AlignRight);
	
	// Tooltip
	setToolTip(QString::fromStdString(btn_item_->name()) + ": " + QString::number(btn_item_->rate()));

}

void ItemIcon::updateItemCount(const float& count) {
	btn_item_->setRate(count);
	item_count_label_->setText(util::formatItemNumber(static_cast<int>(btn_item_->rate())));
	setToolTip(QString::fromStdString(btn_item_->name()) + ": " + QString::number(count));
}

void ItemIcon::setLabelCount(float count) {
    item_count_label_->setText(util::formatItemNumber(static_cast<int>(count)));
    setToolTip(QString::fromStdString(btn_item_->name()) + ": " + QString::number(count));
}

void ItemIcon::setCleared() {
    setStyleSheet("background-color: #00FF00;");
}

} // namespace ui