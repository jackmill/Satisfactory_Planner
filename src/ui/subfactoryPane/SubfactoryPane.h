/**
 * @project Satisfactory_Planner
 * @file SubfactoryPane.h
 *
 * @author Jackson Miller
 * @date 2021-09-17
 * @copyright (c) 2021 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_SUBFACTORYPANE_H
#define SATISFACTORY_PLANNER_SUBFACTORYPANE_H

#include <QWidget>
#include <QSplitter>
#include <QVBoxLayout>
#include <QToolBar>
#include <QListView>

#include "SubfactoryInfo.h"
#include "SubfactoryListModel.h"

#include "plan/Factory.h"

namespace ui {

class SubfactoryPane : public QWidget {
  Q_OBJECT
  public:
	SubfactoryPane(plan::Factory* factory, data::Library* db, QWidget *parent = nullptr);


	plan::Subfactory* selectedSubfactory();

  private:
	struct Actions {
		QAction* act_add = nullptr;
		QAction* act_edit = nullptr;
		QAction* act_delete = nullptr;
	};
	
	Actions actions_;
	QToolBar* toolbar_ = nullptr;

    data::Library* db_;
    plan::Factory* factory_;

    SubfactoryListModel* subfactory_model_ = nullptr;
    QListView* subfactory_list_ = nullptr;
	
	QVBoxLayout *layout_ = nullptr;
	
	void InitToolbar();

  private Q_SLOTS:
    void S_AddSubfactory();
    void S_EditSubfactory();
    void S_RemoveSubfactory();

  Q_SIGNALS:
    void S_selectedSubfactoryChanged();
    void S_factoryChanged();
	
};

} // namespace ui

#endif //SATISFACTORY_PLANNER_SUBFACTORYPANE_H
