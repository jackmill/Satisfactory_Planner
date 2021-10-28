/**
 * @project Satisfactory_Planner
 * @file ProductionTable.h
 *
 * @author Jackson Miller
 * @date 2021-09-18
 * @copyright (c) 2021 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_PRODUCTIONTABLE_H
#define SATISFACTORY_PLANNER_PRODUCTIONTABLE_H

#include <vector>

#include <QWidget>
#include <QGridLayout>

#include "data/Library.h"
#include "plan/Factory.h"

namespace ui {

class ProductionTable : public QWidget {
    Q_OBJECT
  public:
    ProductionTable(plan::Subfactory &subfactory, std::shared_ptr<data::Library> db, QWidget* parent=nullptr);

  private:
    plan::Subfactory& subfactory_;
    std::shared_ptr<data::Library> db_;

    std::vector<std::vector<QWidget>> table_;

    QGridLayout* layout_ = nullptr;

    enum class column {
        Checked = 0,
        Product,
        Recipe,
        Building,
        Power,
        Byproduct,
        Ingredients
    };

    void initHeader();
};

} // namespace ui

#endif //SATISFACTORY_PLANNER_PRODUCTIONTABLE_H
