/**
 * @project Satisfactory_Planner
 * @file TableIcon.cpp
 * 
 * @author Jackson Miller
 * @date 2022-01-10
 * @copyright (c) 2022 Jackson Miller
 */

#include <QIcon>

#include "TableIcon.h"
#include "../util.h"

namespace ui {

TableIcon::TableIcon(const QString& icon_label, QWidget* parent) :
		QPushButton(parent) {

	setFixedSize(kSize_);
	layout_ = new QVBoxLayout(this);
	layout_->setContentsMargins(2, 2, 2, 2);
	layout_->addSpacerItem(new QSpacerItem(TableIcon::kSize_.width(), TableIcon::kSize_.height()));

	setIcon(util::itemIconFromDisplayName(icon_label));
	setIconSize(TableIcon::kSize_ * 0.9);
}

TableIcon::TableIcon(const QString& icon_label, int rate, QWidget* parent) :
		TableIcon(icon_label, parent) {
	auto* label = new QLabel(QString::number(rate), this);
	formatIconLabel(label);

	layout_->addWidget(label, Qt::AlignRight, Qt::AlignRight);
}

TableIcon::TableIcon(const QString& icon_label, float rate, QWidget* parent) :
		TableIcon(icon_label, parent) {
	auto* label = new QLabel(util::formatItemNumber(static_cast<int>(rate)), this);
	formatIconLabel(label);

	layout_->addWidget(label, Qt::AlignRight, Qt::AlignRight);
}

void TableIcon::formatIconLabel(QLabel* label) {
	auto label_font = QFont(label->font());
	label_font.setPixelSize(kSize_.height() / 4);
	label->setFont(label_font);
	label->setAlignment(Qt::AlignRight);
	label->setStyleSheet("font: bold; color: white; background-color: #E59344; border-radius: 3px; margin: 1px");
}

}