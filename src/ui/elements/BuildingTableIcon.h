/**
 * @project Satisfactory_Planner
 * @file BuildingTableIcon.h
 * 
 * @author Jackson Miller
 * @date 2022-01-14
 * @copyright (c) 2022 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_BUILDINGTABLEICON_H
#define SATISFACTORY_PLANNER_BUILDINGTABLEICON_H

#include "TableIcon.h"

namespace ui {

class BuildingTableIcon final : public TableIcon {
  public:
	BuildingTableIcon(const QString& icon_label, float rate, QWidget* parent = nullptr);

};

} // namespace ui

#endif //SATISFACTORY_PLANNER_BUILDINGTABLEICON_H
