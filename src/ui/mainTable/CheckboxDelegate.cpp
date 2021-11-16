/**
 * @project Satisfactory_Planner
 * @file CheckboxDelegate.cpp
 * 
 * @author Jackson Miller
 * @date 2021-11-08
 * @copyright (c) 2021 Jackson Miller
 */

#include "CheckboxDelegate.h"

namespace ui {

CheckboxDelegate::CheckboxDelegate(QCheckBox *checkbox, QObject *parent) :
    checkbox_(checkbox),
    QStyledItemDelegate(parent) {

}

QWidget *CheckboxDelegate::createEditor(QWidget *parent,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const {
    checkbox_->setParent(parent);
    return checkbox_;
}

void CheckboxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                            const QModelIndex &index) const {
    editor->setVisible(true);
    QStyledItemDelegate::updateEditorGeometry(editor, option, index);
}

void CheckboxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {

}

}