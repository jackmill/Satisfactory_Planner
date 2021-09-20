/**
 * @file subfactoryPane.cpp
 * Created by jackm on 9/17/2021
 */



#include "SubfactoryPane.h"

namespace ui {

SubfactoryPane::SubfactoryPane(QWidget *parent) :
	QWidget(parent) {
	
	layout_ = new QVBoxLayout(this);
	
	InitToolbar();
}

void SubfactoryPane::InitToolbar() {
	toolbar_ = new QToolBar(this);
	
	// Actions
	actions_.act_add = new QAction("+", this);
	actions_.act_edit = new QAction("i", this);
	actions_.act_delete = new QAction("-", this);
	
	toolbar_->addAction(actions_.act_add);
	toolbar_->addAction(actions_.act_edit);
	toolbar_->addAction(actions_.act_delete);
}

} // namespace ui