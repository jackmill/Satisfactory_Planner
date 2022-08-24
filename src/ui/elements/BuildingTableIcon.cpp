/**
 * @project Satisfactory_Planner
 * @file BuildingTableIcon.cpp
 * 
 * @author Jackson Miller
 * @date 2022-01-14
 * @copyright (c) 2022 Jackson Miller
 */

#include <QLabel>
#include <QRegularExpression>

#include "BuildingTableIcon.h"

namespace ui {

BuildingTableIcon::BuildingTableIcon(const QString& icon_label, float rate, QWidget* parent) :
	TableIcon(icon_label, parent) {

	auto label_string = QString::number(rate, 'f', 2);
	// Remove trailing zeroes
	label_string.remove(QRegularExpression("\\.?0+$"));

	auto* label = new QLabel(label_string, this);
	formatIconLabel(label);

	layout_->addWidget(label, Qt::AlignRight, Qt::AlignRight);
}

}
