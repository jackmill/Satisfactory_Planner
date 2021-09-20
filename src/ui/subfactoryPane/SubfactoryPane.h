/**
 * @file subfactoryPane.h
 * Created by jackm on 9/17/2021
 */

#ifndef SATISFACTORY_PLANNER_SUBFACTORYPANE_H
#define SATISFACTORY_PLANNER_SUBFACTORYPANE_H

#include <QWidget>
#include <QSplitter>
#include <QVBoxLayout>
#include <QToolBar>

#include "SubfactoryInfo.h"

namespace ui {

class SubfactoryPane : public QWidget {
  public:
	SubfactoryPane(QWidget *parent = nullptr);
  
  private:
	struct Actions {
		QAction* act_add = nullptr;
		QAction* act_edit = nullptr;
		QAction* act_delete = nullptr;
	};
	
	Actions actions_;
	QToolBar* toolbar_;
	
	QVBoxLayout *layout_ = nullptr;
	
	void InitToolbar();
	
};

} // namespace ui

#endif //SATISFACTORY_PLANNER_SUBFACTORYPANE_H
