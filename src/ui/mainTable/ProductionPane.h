/**
 * @project Satisfactory_Planner
 * @file ProductionPane.h
 * 
 * @author Jackson Miller
 * @date 2021-10-06
 * @copyright (c) 2021 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_PRODUCTIONPANE_H
#define SATISFACTORY_PLANNER_PRODUCTIONPANE_H

#include <QWidget>
#include <QGridLayout>
#include <QBoxLayout>
#include <QGroupBox>
#include <QTableView>
#include <QAction>

#include "ProductionTableModel.h"
#include "SubfacItemListModel.h"
#include "TargetModel.h"

#include "plan/Factory.h"

namespace ui {

class ProductionPane final : public QWidget {
    Q_OBJECT
  public:
    ProductionPane(const std::shared_ptr<plan::Subfactory>& subfactory, std::shared_ptr<data::Library> db, QWidget* parent = nullptr);


    void resizeAll();
	void changeSubfactory(std::shared_ptr<plan::Subfactory> subfactory);

  private:
    plan::Subfactory_Ptr subfactory_;
    std::shared_ptr<data::Library> db_;

    QGroupBox* targets_widget_ = nullptr;
    QVBoxLayout* targets_layout_ = nullptr;
    QTableView* targets_ = nullptr;
    TargetModel* targets_model_ = nullptr;

    QGroupBox* byproducts_widget_ = nullptr;
    QVBoxLayout* byproducts_layout_ = nullptr;
    QTableView* byproducts_ = nullptr;
    SubfacItemListModel* byproducts_model_ = nullptr;

    QGroupBox* ingredients_widget_ = nullptr;
    QVBoxLayout* ingredients_layout_ = nullptr;
    QTableView* ingredients_ = nullptr;
    SubfacItemListModel* ingredients_model_ = nullptr;

    QTableView* production_table_ = nullptr;
    ProductionTableModel* table_model_ = nullptr;

    QWidget* header_ = nullptr;
    QHBoxLayout* header_layout_ = nullptr;
    QVBoxLayout* layout_ = nullptr;

    struct Actions {
        // targets
        QAction* target_act_new = nullptr;
        QAction* target_act_add_to_table = nullptr;
        QAction* target_act_edit = nullptr;
        QAction* target_act_del = nullptr;

        // ingredients
        QAction* ingredient_act_add_to_table = nullptr;
    };

    Actions actions_;

    void initTargets();
    void initByproducts();
    void initIngredients();
    void initTable();
    void initActions();

  private Q_SLOTS:
    void S_addNewTarget();
    void S_editTarget(const QModelIndex &index);
    void S_removeTarget(const QModelIndex& index);
    void S_addToTable(std::shared_ptr<plan::ProductTarget> target);
	void S_refreshAll();
	void S_targetSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

  Q_SIGNALS:
    void S_factoryChanged();
};

}

#endif //SATISFACTORY_PLANNER_PRODUCTIONPANE_H
