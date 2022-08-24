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

SubfactoryListModel::SubfactoryListModel(plan::Factory* factory, QObject *parent) :
    factory_(factory),
    QAbstractListModel(parent) {
    assert(factory_);
}

bool SubfactoryListModel::updateSubfactory(int row, const plan::Subfactory &subfactory) {
    if (row >= factory_->subfactories_.size()) {
        return false;
    }

    factory_->subfactories_.at(row)->setLabel(subfactory.label());
    factory_->subfactories_.at(row)->setIcon(subfactory.icon());
    Q_EMIT(dataChanged(createIndex(row, 0), createIndex(row, 0)));
    return true;
}

int SubfactoryListModel::rowCount(const QModelIndex &parent) const {
    return factory_->numSubfactories();
}

QVariant SubfactoryListModel::data(const QModelIndex &index, int role) const {
    const auto subfactory = factory_->subfactoryAt(index.row());

    if (role == Qt::ItemDataRole::DisplayRole) {
        return QString::fromStdString(subfactory->label());
    } else if (role == Qt::ItemDataRole::DecorationRole) {
        return QIcon(QString(":/icon/%1").arg(QString::fromStdString(subfactory->icon())));
    }

    return {};
}

bool SubfactoryListModel::insertRow(int startRow, const QModelIndex& parent,
                                    const plan::Subfactory& subfactory) {
    beginInsertRows(parent, startRow, startRow);
    factory_->addSubfactory(subfactory);
    endInsertRows();

    return true;
}

bool SubfactoryListModel::removeRows(int startRow, int count, const QModelIndex &parent) {
    if (count == 0) {
        return false;
    }

    const int end_row = startRow + count - 1;
    beginRemoveRows(parent, startRow, end_row);
    factory_->subfactories_.erase(factory_->subfactories_.begin() + startRow,
                                  factory_->subfactories_.begin() + (end_row + 1));
    endRemoveRows();

    return true;
}

}