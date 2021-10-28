/**
 * @project Satisfactory_Planner
 * @file SubfactoryListModel.cpp
 * 
 * @author Jackson Miller
 * @date 2021-10-06
 * @copyright (c) 2021 Jackson Miller
 */

#include <QIcon>

#include "SubfactoryListModel.h"

namespace ui {

SubfactoryListModel::SubfactoryListModel(std::shared_ptr<plan::Factory> factory, QObject *parent) :
    factory_(std::move(factory)),
    QAbstractListModel(parent) {
    assert(factory_);
}

bool SubfactoryListModel::updateSubfactory(int row, const plan::Subfactory &subfactory) {
    if (row >= factory_->subfactories_.size()) {
        return false;
    }

    factory_->subfactories_[row].setLabel(subfactory.label());
    factory_->subfactories_[row].setIcon(subfactory.icon());
    Q_EMIT(dataChanged(createIndex(row, 0), createIndex(row, 0)));
    return true;
}

int SubfactoryListModel::rowCount(const QModelIndex &parent) const {
    return factory_->subfactories_.size();
}

QVariant SubfactoryListModel::data(const QModelIndex &index, int role) const {
    const auto subfac = factory_->subfactories_.at(index.row());

    if (role == Qt::ItemDataRole::DisplayRole) {
        return QString::fromStdString(subfac.label());
    } else if (role == Qt::ItemDataRole::DecorationRole) {
        return QIcon(QString::fromStdString(subfac.icon()));
    }

    return {};
}

bool SubfactoryListModel::insertRows(int startRow, int count, const QModelIndex &parent) {
    beginInsertRows(parent, startRow, startRow + count - 1);
    factory_->subfactories_.reserve(factory_->subfactories_.size() + count);
    for (int row = startRow; row < startRow + count; ++row) {
        factory_->subfactories_.emplace(factory_->subfactories_.cbegin() + row);
    }
    endInsertRows();

    return true;
}

bool SubfactoryListModel::removeRows(int startRow, int count, const QModelIndex &parent) {
    if (count == 0) {
        return false;
    }

    const int endRow = startRow + count - 1;
    beginRemoveRows(parent, startRow, endRow);
    factory_->subfactories_.erase(factory_->subfactories_.begin() + startRow,
                                  factory_->subfactories_.begin() + (endRow + 1));
    endRemoveRows();

    return true;
}

}