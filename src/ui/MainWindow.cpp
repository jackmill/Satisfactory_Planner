//
// Created by Jackson Miller on 9/13/21.
//
#include <QMenuBar>
#include <fstream>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

#include "MainWindow.h"
#include "AboutDialog.h"
#include "projectconfig.h"

namespace ui {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle(tr(config::kProject_display_name));

    InitActions();
    InitMenu();
    InitRecipes();
}

void MainWindow::InitActions() {
    // File
    // Quit
    actions_.act_quit = new QAction(QIcon::fromTheme("application-exit"), tr("&Quit"), this);
    actions_.act_quit->setShortcut(QKeySequence::Quit);
    connect(actions_.act_quit, &QAction::triggered, this, &MainWindow::close);

    // About
    actions_.act_help = new QAction(tr("&About"), this);
    connect(actions_.act_help, &QAction::triggered, this, &MainWindow::SAbout);
}

void MainWindow::InitMenu() {
    // File
    QMenu* menu_file = menuBar()->addMenu(tr("&File"));
    menu_file->addAction(actions_.act_quit);

    QMenu* menu_help = menuBar()->addMenu(tr("&Help"));
    menu_help->addAction(actions_.act_help);
}

/**
 * PROOF OF CONCEPT
 */
void MainWindow::InitRecipes() {
    recipe_list_ = new QComboBox(this);
    recipe_list_->setFixedSize(300, 75);
    QStringList recipe_list;

    std::ifstream json_file;
    json_file.exceptions(std::fstream::failbit | std::fstream::badbit);
    try {
        json_file.open("resources/docs.json");
    } catch (const std::fstream::failure &e){
        std::cerr << e.what() << std::endl;
        this->close();
    }

    nlohmann::json docs = nlohmann::json::parse(json_file);

    for (auto native_class : docs) {
        if (native_class.at("NativeClass") == "Class'/Script/FactoryGame.FGRecipe'") {
            for (auto class_item : native_class.at("Classes")) {
                std::string item;
                recipe_list.push_back(QString::fromStdString(class_item.at("mDisplayName").get_to(item)));
            }
        }
    }

    recipe_list_->addItems(recipe_list);
}

void MainWindow::SAbout() {
    auto *about_dialog = new AboutDialog(this);
    about_dialog->exec();
}

} // namespace ui