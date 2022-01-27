/**
 * @project Satisfactory_Planner
 * @file RecipeSelectDialog.h
 * 
 * @author Jackson Miller
 * @date 2021-11-03
 * @copyright (c) 2021 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_RECIPESELECTDIALOG_H
#define SATISFACTORY_PLANNER_RECIPESELECTDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QTableView>
#include <QVBoxLayout>

#include "RecipeSelectModel.h"
#include "data/Library.h"

namespace ui {

class RecipeSelectDialog : public QDialog {
    Q_OBJECT
  public:
    explicit RecipeSelectDialog(std::vector<data::Recipe> recipes, QWidget* parent = nullptr);

    data::Recipe getSelectedRecipe();

  private:
    std::vector<data::Recipe> recipes_;

    QTableView* recipe_table_ = nullptr;
    RecipeSelectModel* recipe_model_ = nullptr;

    QDialogButtonBox* actions_ = nullptr;

    QVBoxLayout* layout_ = nullptr;

	[[nodiscard]] int tableWidth() const;
};

}

#endif //SATISFACTORY_PLANNER_RECIPESELECTDIALOG_H
