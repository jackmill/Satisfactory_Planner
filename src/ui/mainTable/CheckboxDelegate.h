/**
 * @project Satisfactory_Planner
 * @file CheckboxDelegate.h
 * 
 * @author Jackson Miller
 * @date 2021-11-08
 * @copyright (c) 2021 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_CHECKBOXDELEGATE_H
#define SATISFACTORY_PLANNER_CHECKBOXDELEGATE_H

#include <QStyledItemDelegate>
#include <QCheckBox>

namespace ui {

class CheckboxDelegate : public QStyledItemDelegate {
    Q_OBJECT
  public:
    explicit CheckboxDelegate(QCheckBox* checkbox, QObject* parent = nullptr);

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex &index) const override;

  private:
    QCheckBox* checkbox_;
};

}

#endif //SATISFACTORY_PLANNER_CHECKBOXDELEGATE_H
