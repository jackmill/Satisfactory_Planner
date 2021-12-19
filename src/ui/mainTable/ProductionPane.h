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
#include "TargetModel.h"
#include "IngredientsModel.h"

#include "plan/Factory.h"

namespace ui {

class ProductionPane : public QWidget {
    Q_OBJECT
  public:
    ProductionPane(plan::Subfactory &subfactory, std::shared_ptr<data::Library> db, QWidget* parent = nullptr);

  private:
    plan::Subfactory& subfactory_;
    std::shared_ptr<data::Library> db_;

    // TODO: This is all way too complicated.  Use just one model for all tables, with a more global column enum to differentiate
    QGroupBox* targets_widget_ = nullptr;
    QVBoxLayout* targets_layout_ = nullptr;
    QTableView* targets_ = nullptr;
    TargetModel* targets_model_ = nullptr;

    QGroupBox* byproducts_widget_ = nullptr;
    QVBoxLayout* byproducts_layout_ = nullptr;
    QTableView* byproducts_ = nullptr;

    QGroupBox* ingredients_widget_ = nullptr;
    QVBoxLayout* ingredients_layout_ = nullptr;
    QTableView* ingredients_ = nullptr;
    IngredientsModel* ingredients_model_ = nullptr;

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
    };

    Actions actions_;

    void initTargets();
    void initByproducts();
    void initIngredients();
    void initTable();
    void initActions();

    bool AddNewProductLineOk();

  private Q_SLOTS:
    void S_updateTable();
    void S_updateByproducts();
    void S_updateIngredients();
//    void S_editSelectedTarget();


//    void updateTargets();
//    void addTarget();
//    void removeTarget(const data::Item &item);
};

}

#endif //SATISFACTORY_PLANNER_PRODUCTIONPANE_H
