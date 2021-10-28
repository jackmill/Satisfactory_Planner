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

#include "ProductionTable.h"

#include "plan/Factory.h"

namespace ui {

class ProductionPane : public QWidget {
    Q_OBJECT
  public:
    ProductionPane(plan::Subfactory &subfactory, std::shared_ptr<data::Library> db, QWidget* parent = nullptr);



  private:
    plan::Subfactory& subfactory_;
    std::shared_ptr<data::Library> db_;

    QGroupBox* targets_widget_ = nullptr;
    QHBoxLayout* targets_ = nullptr;
    QGroupBox* byproducts_widget_ = nullptr;
    QHBoxLayout* byproducts_ = nullptr;
    QGroupBox* ingredients_widget_ = nullptr;
    QHBoxLayout* ingredients_ = nullptr;
    QGroupBox* production_widget_ = nullptr;
    ProductionTable* production_table_ = nullptr;

    QWidget* header_ = nullptr;
    QHBoxLayout* header_layout_ = nullptr;
    QVBoxLayout* layout_ = nullptr;

  private Q_SLOTS:
    void updateTable();
    void updateTargets();
    void updateByproducts();
    void updateIngredients();
    void addTarget();
};

}

#endif //SATISFACTORY_PLANNER_PRODUCTIONPANE_H
