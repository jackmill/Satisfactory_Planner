/**
 * @project Satisfactory_Planner
 * @file ProductionTableModel.h
 * 
 * @author Jackson Miller
 * @date 2021-11-01
 * @copyright (c) 2021 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_PRODUCTIONTABLEMODEL_H
#define SATISFACTORY_PLANNER_PRODUCTIONTABLEMODEL_H

#include <QAbstractTableModel>

#include "plan/Subfactory.h"
#include "data/Library.h"

namespace ui {

class ProductionTableModel final : public QAbstractTableModel {
    Q_OBJECT
  public:
    explicit ProductionTableModel(std::shared_ptr<plan::Subfactory> subfactory, std::shared_ptr<data::Library> db, QObject* parent = nullptr);

    [[nodiscard]] int rowCount(const QModelIndex &parent) const final;
    [[nodiscard]] int columnCount(const QModelIndex &parent) const final { return static_cast<int> (Column::Ingredient4) + 1; };
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const final;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation, int role) const final;
    [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const final;

    bool insertRows(int startRow, const QModelIndex &parent, plan::ProductLine product_line);
    bool removeRows(int startRow, int count, const QModelIndex &parent) final;
    [[nodiscard]] std::shared_ptr<data::Item> getRowTarget(const QModelIndex &index) const;

    void refreshModel();

    enum class Column {
        Checked = 0,
        Product,
        Recipe,
		Percentage,
        Building,
		ClockSpeed,
        Power,
        Byproduct,
        Ingredient1,
        Ingredient2,
        Ingredient3,
        Ingredient4
    };

  private:
    std::shared_ptr<plan::Subfactory> subfactory_;
    std::shared_ptr<data::Library> db_;

    [[nodiscard]] static QVariant ingredientData(int col_index, const plan::ProductLine &product_line);
    [[nodiscard]] static QIcon ingredientIcon(int col_index, const plan::ProductLine& product_line);
};

}

#endif //SATISFACTORY_PLANNER_PRODUCTIONTABLEMODEL_H
