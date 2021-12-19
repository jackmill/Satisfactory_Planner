/**
 * @project Satisfactory_Planner
 * @file ItemIconDelegate.h
 * 
 * @author Jackson Miller
 * @date 2021-11-08
 * @copyright (c) 2021 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_ITEMICONDELEGATE_H
#define SATISFACTORY_PLANNER_ITEMICONDELEGATE_H

#include <QStyledItemDelegate>

#include "../elements/ItemIcon.h"
#include "plan/Subfactory.h"

namespace ui {

class ItemIconDelegate : public QStyledItemDelegate {
  Q_OBJECT
  public:
    explicit ItemIconDelegate(QObject* parent = nullptr) :
        QStyledItemDelegate(parent) {};

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

  private:

};

}

#endif //SATISFACTORY_PLANNER_ITEMICONDELEGATE_H
