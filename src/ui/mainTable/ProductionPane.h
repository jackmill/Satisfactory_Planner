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

#include <memory>

#include "ProductionTableModel.h"
#include "IngredientsModel.h"
#include "ProductModel.h"
#include "ByproductsModel.h"

#include "plan/Factory.h"

namespace ui {

class ProductionPane final : public QWidget {
    Q_OBJECT
  public:
    ProductionPane(plan::Subfactory* subfactory, data::Library* db, QWidget* parent = nullptr);


    void resizeAll();
	void changeSubfactory(plan::Subfactory* subfactory);

  private:
    std::unique_ptr<plan::Subfactory*> subfactory_;
    data::Library* db_;

    QGroupBox* products_widget_ = nullptr;
    QVBoxLayout* products_layout_ = nullptr;
    QTableView* products_ = nullptr;
    ProductModel* products_model_ = nullptr;

    QGroupBox* byproducts_widget_ = nullptr;
    QVBoxLayout* byproducts_layout_ = nullptr;
    QTableView* byproducts_ = nullptr;
    ByproductsModel* byproducts_model_ = nullptr;

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
        QAction* product_act_new = nullptr;
        QAction* product_act_add_to_table = nullptr;
        QAction* product_act_edit = nullptr;
        QAction* product_act_del = nullptr;

        // ingredients
        QAction* ingredient_act_add_to_table = nullptr;
    };

	struct ProdTableActions {
		// Done

		// Product

		// Recipe
		QAction* recipe_change = nullptr;

		// Percent
		QAction* percent_edit = nullptr;

		// Building

		// Clock Speed
		QAction* clock_edit = nullptr;

		// Power

		// Byproduct
		QAction* byproduct_use = nullptr;

		// Ingredients

		// All Columns
		QAction* delete_row = nullptr;

		void setAllInvisible() const {
			recipe_change->setVisible(false);
			percent_edit->setVisible(false);
			clock_edit->setVisible(false);
			byproduct_use->setVisible(false);
		}
	};

    Actions actions_;
	ProdTableActions prod_table_actions_;

    void initProducts();
    void initByproducts();
    void initIngredients();
    void initTable();
    void initActions();

  private Q_SLOTS:
    void S_addNewTarget();
    void S_editTarget(const QModelIndex &index);
    void S_removeTarget(const QModelIndex& index);
    void S_addToTable(plan::TableItem* target);
	void S_refreshAll();
	void S_productSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
	void S_prodTableContextMenu(const QModelIndex& index);
	void S_editPercent(const QModelIndex& index);
	void S_editClockSpeed(const QModelIndex& index);
	void S_removeProductLine(const QModelIndex& index);
	void S_changeProductLineRecipe(const QModelIndex& index);

  Q_SIGNALS:
    void S_factoryChanged();
};

}

#endif //SATISFACTORY_PLANNER_PRODUCTIONPANE_H
