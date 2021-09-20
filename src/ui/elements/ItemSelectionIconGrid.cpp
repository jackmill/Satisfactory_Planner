/**
 * @file ItemSelectionIconGrid.cpp
 * Created by jackm on 9/19/2021
 */


#include "ItemSelectionIconGrid.h"
#include "BasicItemButton.h"

namespace ui {

ItemSelectionIconGrid::ItemSelectionIconGrid(QWidget *parent) :
		QWidget(parent){
	layout_ = new QGridLayout(this);
}

void ItemSelectionIconGrid::addButton(QString item_name, const int &x, const int &y) {
	layout_->addWidget(new BasicItemButton(std::move(item_name)), x, y, Qt::AlignCenter, Qt::AlignCenter);
}

} // namespace ui