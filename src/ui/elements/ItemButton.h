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

#include <QAction>

#include "ItemIcon.h"

namespace ui {

class ItemButton : public ItemIcon {
    Q_OBJECT
  public:
    ItemButton(std::shared_ptr<data::Item> item, std::shared_ptr<data::Library> db, QWidget* parent = nullptr);

    void editItem(const std::shared_ptr<data::Item>& item);

    struct Actions {
        QAction* act_add_to_table = nullptr;
        QAction* act_edit = nullptr;
        QAction* act_delete = nullptr;
    };

    Actions actions_;

  private:
    std::shared_ptr<data::Library> db_;

    void initMenu();


};

}

#endif //SATISFACTORY_PLANNER_ITEMBUTTON_H
