/**
 * @file ItemSelectionIconGrid.h
 * Created by jackm on 9/19/2021
 */

#ifndef SATISFACTORY_PLANNER_ITEMSELECTIONICONGRID_H
#define SATISFACTORY_PLANNER_ITEMSELECTIONICONGRID_H

#include <QWidget>
#include <QGridLayout>

#include "BasicItemButton.h"

namespace ui {

class ItemSelectionIconGrid : public QWidget {
  public:
	ItemSelectionIconGrid(QWidget* parent);
	
	void addButton(QString item_name, const int &x, const int &y);
	
  private:
	QGridLayout* layout_ = nullptr;
	
};

}

#endif //SATISFACTORY_PLANNER_ITEMSELECTIONICONGRID_H
