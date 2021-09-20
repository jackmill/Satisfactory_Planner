/**
 * @file ItemButtonLabel.h
 * Created by jackm on 9/18/2021
 */

#ifndef SATISFACTORY_PLANNER_ITEMBUTTONLABEL_H
#define SATISFACTORY_PLANNER_ITEMBUTTONLABEL_H

#include <QLabel>
#include <QPaintEvent>

class ItemButtonLabel : public QLabel {
  public:
	ItemButtonLabel(const QString &text, QWidget* parent = nullptr);

};

#endif //SATISFACTORY_PLANNER_ITEMBUTTONLABEL_H
