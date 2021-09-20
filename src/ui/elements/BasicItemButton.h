/**
 * @file BasicItemButton.h
 * Created by jackm on 9/19/2021
 */

#ifndef SATISFACTORY_PLANNER_BASICITEMBUTTON_H
#define SATISFACTORY_PLANNER_BASICITEMBUTTON_H

#include <QPushButton>

namespace ui {

class BasicItemButton : public QPushButton {
	Q_OBJECT
	
  public:
	BasicItemButton(QString display_name, QWidget* parent = nullptr);
	
  protected:
	QString item_name_;
	static QIcon itemIconFromDisplayName(const QString &display_name);
};

} // namespace ui

#endif //SATISFACTORY_PLANNER_BASICITEMBUTTON_H
