/**
 * @project Satisfactory_Planner
 * @file ItemViewModel.cpp
 * 
 * @author Jackson Miller
 * @date 2021-11-07
 * @copyright (c) 2021 Jackson Miller
 */

#include "ItemViewModel.h"

namespace ui {

ItemViewModel::ItemViewModel(plan::Subfactory &subfactory, QObject *parent) :
    subfactory_(subfactory),
    QAbstractTableModel(parent) {

}

QVariant ItemViewModel::headerData(int section, Qt::Orientation orientation, int role) const {
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

}