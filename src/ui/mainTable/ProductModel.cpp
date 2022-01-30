/**
 * @project Satisfactory_Planner
 * @file ProductModel.cpp
 * 
 * @author Jackson Miller
 * @date 2021-11-05
 * @copyright (c) 2021 Jackson Miller
 */

#include "../util.h"
#include "../elements/ItemSelectionDialog.h"

#include "ProductModel.h"

namespace ui {

ProductModel::ProductModel(std::shared_ptr<data::Library> db, plan::Subfactory_Ptr subfactory, QObject *parent) :
        db_(std::move(db)),
        subfactory_(std::move(subfactory)),
        QAbstractTableModel(parent) {
    assert(subfactory_);
    assert(db_);
}

QVariant ProductModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::ItemDataRole::DisplayRole || orientation != Qt::Horizontal) {
        return {};
    }

    const auto column = static_cast<Column> (section);
    switch (column) {
        case Column::kItem :      return tr("Target");
        case Column::kRate :      return tr("Rate");
    }

    return {};
}

QVariant ProductModel::data(const QModelIndex &index, int role) const {
    const auto target = (*subfactory_)->products_.at(index.row());
    const auto column = static_cast<Column> (index.column());

    if (role == Qt::ItemDataRole::DisplayRole) {
        if (column == Column::kItem) {
            return QString::fromStdString(target->name());

        } else if (column == Column::kRate) {
            return target->rate();

        }

    } else if (role == Qt::ItemDataRole::DecorationRole) {
        if (column == Column::kItem) {
            return util::itemIconFromDisplayName(QString::fromStdString(target->name()));

        }

    } else if (role == Qt::ItemDataRole::ForegroundRole) {
		if (!(*subfactory_)->isOnTable(target)) {
			return QColor(Qt::darkGray);
		} else if (target->completion() < 100) {
			return QColor(Qt::yellow);
		} else if (target->completion() > 100) {
			return QColor(Qt::red);
		}

	} else if (role == Qt::ItemDataRole::EditRole) {
		if (column == Column::kRate) {
			return target->rate();
		}
	}

    return {};
}

bool ProductModel::setData(const QModelIndex& index, const QVariant& value, int role) {
	const auto column = static_cast<Column> (index.column());
	const auto target = (*subfactory_)->products_.at(index.row());
	bool success = false;

	if (role == Qt::ItemDataRole::EditRole) {
		const auto target_rate = value.value<float>();
		if (column == Column::kRate) {
			target->setRate(target_rate);
			success = true;
		}
	}

	if (success) {
		Q_EMIT(dataChanged(index, index));
	}

	return success;
}

Qt::ItemFlags ProductModel::flags(const QModelIndex& index) const {
	const auto column = static_cast<Column> (index.column());

	if (column == Column::kRate) {
		return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	} else {
		return QAbstractTableModel::flags(index);
	}
}

bool ProductModel::insertRows(int startRow, const QModelIndex &parent, const std::shared_ptr<plan::LineTarget>& new_target) {
    beginInsertRows(parent, startRow, startRow);

    (*subfactory_)->products_.emplace_back(new_target);

    endInsertRows();
    return true;
}

bool ProductModel::removeRows(int startRow, int count, const QModelIndex &parent) {
    if (count == 0 || (*subfactory_)->products_.size() <= 1) {
        return false;
    }

    const int endRow = startRow + count - 1;
    beginRemoveRows(parent, startRow, endRow);
    (*subfactory_)->products_.erase((*subfactory_)->products_.begin() + startRow,
                                    (*subfactory_)->products_.begin() + (endRow + 1));
    endRemoveRows();

    return true;
}

std::shared_ptr<plan::LineTarget> ProductModel::getTarget(const QModelIndex &index) const {
    return (*subfactory_)->products_.at(index.row());
}

void ProductModel::refreshModel() {
	beginResetModel();
	endResetModel();
}

}