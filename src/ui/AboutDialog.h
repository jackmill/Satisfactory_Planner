/**
 * @project Satisfactory_Planner
 * @file AboutDialog.h
 *
 * @author Jackson Miller
 * @date 2021-09-13
 * @copyright (c) 2021 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_ABOUTDIALOG_H
#define SATISFACTORY_PLANNER_ABOUTDIALOG_H

#include <QDialog>

namespace ui {

class AboutDialog : public QDialog {
    Q_OBJECT
  public:
    AboutDialog(QWidget* parent = nullptr);
};

} // namespace ui

#endif //SATISFACTORY_PLANNER_ABOUTDIALOG_H
