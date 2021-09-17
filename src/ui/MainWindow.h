//
// Created by Jackson Miller on 9/13/21.
//

#ifndef SATISFACTORY_PLANNER_MAINWINDOW_H
#define SATISFACTORY_PLANNER_MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>

namespace ui {

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr);

  private:
    struct Actions {
        // File
        QAction* act_quit = nullptr;

        // Help
        QAction* act_help = nullptr;
    };

    Actions actions_;

    QComboBox* recipe_list_ = nullptr;
    void InitRecipes();

    void InitActions();
    void InitMenu();

  private Q_SLOTS:
    // Actions
    void SAbout();
};

} // namespace ui

#endif //SATISFACTORY_PLANNER_MAINWINDOW_H
