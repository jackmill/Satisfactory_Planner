/**
 * @file ItemSelectionDialog.cpp
 * Created by jackm on 9/19/2021
 */

#include "ItemSelectionDialog.h"
#include "ItemSelectionIconGrid.h"

namespace ui {

ItemSelectionDialog::ItemSelectionDialog(QWidget *parent) :
		QDialog(parent) {
	
	layout_ = new QVBoxLayout(this);
	
}

}