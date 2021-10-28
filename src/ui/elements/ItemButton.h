/**
 * @project Satisfactory_Planner
 * @file ItemButton.h
 *
 * @author Jackson Miller
 * @date 2021-10-05
 * @copyright (c) 2021 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_ITEMBUTTON_H
#define SATISFACTORY_PLANNER_ITEMBUTTON_H

#include "ItemIcon.h"

namespace ui {

class ItemButton : public ItemIcon {
    Q_OBJECT
  public:
    ItemButton(data::Item &item, std::shared_ptr<data::Library> db, QWidget* parent = nullptr);

    void selectItem(const data::Item &item);

  private:
    std::shared_ptr<data::Library> db_;

};

}

#endif //SATISFACTORY_PLANNER_ITEMBUTTON_H
