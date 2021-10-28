/**
 * @project Satisfactory_Planner
 * @file MainWindow.h
 *
 * @author Jackson Miller
 * @date 2021-09-13
 * @copyright (c) 2021 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_MAINWINDOW_H
#define SATISFACTORY_PLANNER_MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>
#include <QHBoxLayout>
#include <QSplitter>

#include "data/Library.h"
#include "plan/Factory.h"

#include "subfactoryPane/SubfactoryPane.h"
#include "mainTable/ProductionPane.h"
#include "elements/ItemButton.h"
#include "elements/ItemIcon.h"

namespace ui {

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr);

  private:
    struct Actions {
        // File
		QAction* act_data_source = nullptr;
        QAction* act_quit = nullptr;

        // Help
        QAction* act_help = nullptr;
    };
	
	Actions actions_;
	SubfactoryPane* subfactory_pane_ = nullptr;
    ProductionPane* production_pane_ = nullptr;
	
	QWidget* contents_ = nullptr;
	QHBoxLayout* layout_ = nullptr;
	QSplitter* splitter_ = nullptr;
 
    ItemButton* item_list_ = nullptr;
    ItemIcon* test_icon_ = nullptr;

    std::shared_ptr<data::Library> db_;
    std::shared_ptr<plan::Factory> factory_;

    void InitActions();
    void InitMenu();

    void _TestItemList();
//    void _TestListRecipes();

  private Q_SLOTS:
    // Actions
	void SDataSource();
    void SAbout();

    //
    void SSubfactoryChanged();
};

} // namespace ui

#endif //SATISFACTORY_PLANNER_MAINWINDOW_H
