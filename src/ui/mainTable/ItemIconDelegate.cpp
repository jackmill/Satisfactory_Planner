/**
 * @project Satisfactory_Planner
 * @file ItemIconDelegate.cpp
 * 
 * @author Jackson Miller
 * @date 2021-11-08
 * @copyright (c) 2021 Jackson Miller
 */

#include "ItemIconDelegate.h"
#include "ProductionTableModel.h"

namespace ui {

QWidget *ItemIconDelegate::createEditor(QWidget *parent,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const {
    const auto* model = dynamic_cast<const ProductionTableModel *>(index.model());
    data::Item target = model->getRowTarget(index);
    auto* icon = new ItemIcon(target, parent);
    return icon;
}

}