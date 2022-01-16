/**
 * @project Satisfactory_Planner
 * @file ProductionTableModel.cpp
 * 
 * @author Jackson Miller
 * @date 2021-11-01
 * @copyright (c) 2021 Jackson Miller
 */

#include <QCheckBox>
#include <QLocale>

#include <vector>

#include "ProductionTableModel.h"
#include "recipeSelectDialog/ProductLineEditDialog.h"
#include "../util.h"

namespace ui {

ProductionTableModel::ProductionTableModel(plan::Subfactory_Ptr subfactory, std::shared_ptr<data::Library> db, QObject *parent) :
    subfactory_(std::move(subfactory)),
    db_(std::move(db)),
    QAbstractTableModel(parent) {
    assert(subfactory_);
}

int ProductionTableModel::rowCount(const QModelIndex &parent) const {
    return static_cast<int> ((*subfactory_)->product_lines_.size());
}



QVariant ProductionTableModel::data(const QModelIndex &index, int role) const {
    const auto &product_line = (*subfactory_)->product_lines_.at(index.row());
    const auto column = static_cast<Column> (index.column());

    if (role == Qt::ItemDataRole::DisplayRole) {
        if (column == Column::Recipe) {
	        return QString::fromStdString(product_line.recipe().name());

        } else if (column == Column::Percentage){
			return QString("%1%").arg(product_line.percent());

        } else if (column == Column::ClockSpeed) {
			return QString("%1%").arg(product_line.clock());

		} else if (column == Column::Power) {
            return QString("%1 MW").arg(QLocale(QLocale::system()).toString(product_line.power()));

        }
    } else if (role == Qt::ItemDataRole::CheckStateRole) {
        if (column == Column::Checked) {
            return product_line.isDone() ? Qt::CheckState::Checked : Qt::CheckState::Unchecked;
        }

    } else if (role == Qt::ItemDataRole::DecorationRole) {
        if (column == Column::Product) {
            return util::itemIconFromDisplayName(QString::fromStdString(product_line.target()->name()));
        } else if (column == Column::Building) {
            return util::itemIconFromDisplayName(QString::fromStdString(product_line.recipe().machine().name()));
        } else if (column == Column::Byproduct) {
            // Recipes can only produce a maximum of two products, so we just need to check that the recipe
            // in question produces two and then return whichever is not the targeted product
            std::vector<data::Item> product_list = product_line.calcProducts();
            if (product_list.size() > 1) {
                for (const auto &product : product_list) {
                    if (product != product_line.target()->target()) {
                        return util::itemIconFromDisplayName(QString::fromStdString(product.name()));
                    }
                }
            } else {
                return {};
            }
        }

    } else if (role == Qt::ItemDataRole::EditRole) {
		if (column == Column::Percentage) {
			return product_line.percent();

		} else if (column == Column::ClockSpeed) {
			return product_line.clock();

		}
	} else if (role == Qt::ItemDataRole::ToolTipRole) {
	    if (column == Column::Product) {
		    return QString("%1 : %2").arg(QString::fromStdString(product_line.target()->name()),
										  QLocale(QLocale::system()).toString(product_line.productOutput()));

	    } else if (column == Column::Byproduct) {

		    if (product_line.hasByproduct()) {
			    return QString("%1 : %2").arg(QString::fromStdString(product_line.byproduct().name()),
											  QLocale(QLocale::system()).toString(product_line.byproduct().rate()));
		    }

	    } else if (column == Column::Building) {
		    return QString("%1 : %2").arg(QString::fromStdString(product_line.recipe().machine().name()),
		                                  QLocale(QLocale::system()).toString(product_line.multiplier()));

		} else if (column == Column::Ingredients) {
			QString ingredients_tooltip;
			const std::vector<data::Item>& ingredients = product_line.ingredients();

			for (auto ingredient = ingredients.cbegin();
					ingredient != ingredients.cend();
					++ingredient) {
				ingredients_tooltip += QString("%1 : %2").arg(QString::fromStdString(ingredient->name()),
				                                              QLocale(QLocale::system()).toString(ingredient->rate()));

				if (ingredient != std::prev(ingredients.end())) {
					ingredients_tooltip += "\n";
				}
			}

			return ingredients_tooltip;
		}
    }

    return {};
}

bool ProductionTableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    const auto column = static_cast<Column> (index.column());
    auto &product_line = (*subfactory_)->product_lines_.at(index.row());
    bool success = false;

    if (role == Qt::ItemDataRole::CheckStateRole) {
        const auto checked = value.value<Qt::CheckState>();
        if (column == Column::Checked) {
            product_line.setDone(checked == Qt::Checked);
            success = true;
        }

    } else if (role == Qt::ItemDataRole::EditRole) {
		if (column == Column::Percentage) {
			product_line.setPercent(value.value<float>());
			success = true;

		} else if (column == Column::ClockSpeed) {
			product_line.setClock(value.value<float>());
			success = true;

		}
	}

    if (success) {
		Q_EMIT(dataChanged(index, index));
    }

    return success;
}

QVariant ProductionTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::ItemDataRole::DisplayRole || orientation != Qt::Horizontal) {
        return {};
    }

    const auto column = static_cast<Column> (section);
    switch (column) {
        case Column::Checked :      return tr("Done");
        case Column::Product :      return tr("Product");
        case Column::Recipe :       return tr("Recipe");
		case Column::Percentage :   return "%";
	    case Column::Building :     return tr("Building");
		case Column::ClockSpeed :   return tr("Clock Speed");
        case Column::Power :        return tr("Power");
        case Column::Byproduct :    return tr("Byproduct");
        case Column::Ingredients :  return tr("Ingredients");
    }

    return {};
}

bool ProductionTableModel::insertRows(int startRow, const QModelIndex &parent, plan::ProductLine product_line) {
    beginInsertRows(parent, startRow, startRow);

    (*subfactory_)->product_lines_.push_back(std::move(product_line));

    endInsertRows();
    return true;
}

bool ProductionTableModel::removeRows(int startRow, int count, const QModelIndex &parent) {
    if (count == 0 || (*subfactory_)->product_lines_.empty()) {
        return false;
    }

    const int end_row = startRow + count - 1;
    beginRemoveRows(parent, startRow, end_row);
    (*subfactory_)->product_lines_.erase((*subfactory_)->product_lines_.cbegin() + startRow,
                                     (*subfactory_)->product_lines_.cbegin() + (end_row + 1));
    endRemoveRows();
    refreshModel();
    return true;
}

std::shared_ptr<plan::ProductTarget> ProductionTableModel::getRowTarget(const QModelIndex &index) const {
    return (*subfactory_)->product_lines_.at(index.row()).target();
}

Qt::ItemFlags ProductionTableModel::flags(const QModelIndex &index) const {
    const auto column = static_cast<Column> (index.column());

    switch (column) {
        case Column::Checked:
            return Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable;

		case Column::ClockSpeed:
	    case Column::Percentage:
			return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;

        case Column::Product:
        case Column::Recipe:
        case Column::Building:
        case Column::Power:
        case Column::Byproduct:
		case Column::Ingredients:
            return QAbstractTableModel::flags(index);
    }

    return QAbstractTableModel::flags(index);
}

QVariant ProductionTableModel::ingredientData(int col_index, const plan::ProductLine &product_line) {
    std::vector<data::Item> ingredient_list = product_line.ingredients();

    if (ingredient_list.size() > col_index) {
        return QString("%1 : %2").arg(QString::fromStdString(ingredient_list.at(col_index).name())).arg(ingredient_list.at(col_index).rate());
    } else {
        return {};
    }
}

QIcon ProductionTableModel::ingredientIcon(int col_index, const plan::ProductLine &product_line) {
    std::vector<data::Item> ingredient_list = product_line.ingredients();

    if (ingredient_list.size() > col_index) {
        return util::itemIconFromDisplayName(QString::fromStdString(ingredient_list.at(col_index).name()));
    } else {
        return {};
    }
}

void ProductionTableModel::refreshModel() {
    beginResetModel();
    endResetModel();
}

}