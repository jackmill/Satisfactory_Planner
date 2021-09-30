//
// Created by Jackson Miller on 9/13/21.
//
#include <QMenuBar>
#include <string>
#include <QTextEdit>
#include <QMessageBox>

#include "settings.h"
#include "MainWindow.h"
#include "DataSourceDialog.h"
#include "AboutDialog.h"
#include "projectconfig.h"

namespace ui {

/**
 *
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent)
    : db_ (new gameData::Library),
    QMainWindow(parent) {
    setWindowTitle(tr(config::kProject_display_name));
	
	// Load database from given Docs.json file, either stored or chosen by user
	if (Settings::GetJsonDataPath().isEmpty()) {
		QMessageBox::information(this,
                                 tr("No Docs.json file found"),
                                 tr("Choose Docs.json file path in settings"));

        SDataSource();

	} else {
        *db_ = gameData::Library(Settings::GetJsonDataPath().toStdString());
    }
	
	contents_ = new QWidget(this);
	setCentralWidget(contents_);
	
	layout_ = new QHBoxLayout(contents_);
	splitter_ = new QSplitter(contents_);
	layout_->addWidget(splitter_);
	
	subfactory_pane_ = new SubfactoryPane(contents_);
	splitter_->addWidget(subfactory_pane_);

    InitActions();
    InitMenu();

    _TestItemList();

    recipes_from_item_ = new QComboBox(contents_);
    splitter_->addWidget(recipes_from_item_);

    connect(item_list_, &QComboBox::currentTextChanged, this, &MainWindow::_TestListRecipes);
}

/**
 *
 */
void MainWindow::InitActions() {
    // File
	// Data Source
	actions_.act_data_source = new QAction(tr("Select &Data Source..."), this);
	connect(actions_.act_data_source, &QAction::triggered, this, &MainWindow::SDataSource);
	
    // Quit
    actions_.act_quit = new QAction(QIcon::fromTheme("application-exit"), tr("&Quit"), this);
    actions_.act_quit->setShortcut(QKeySequence::Quit);
    connect(actions_.act_quit, &QAction::triggered, this, &MainWindow::close);

    // About
    actions_.act_help = new QAction(tr("&About"), this);
    connect(actions_.act_help, &QAction::triggered, this, &MainWindow::SAbout);
}

/**
 *
 */
void MainWindow::InitMenu() {
    // File
    QMenu* menu_file = menuBar()->addMenu(tr("&File"));
	menu_file->addAction(actions_.act_data_source);
	menu_file->addSeparator();
    menu_file->addAction(actions_.act_quit);

    QMenu* menu_help = menuBar()->addMenu(tr("&Help"));
    menu_help->addAction(actions_.act_help);
}

void MainWindow::_TestItemList() {
    item_list_ = new QComboBox(contents_);

    QStringList item_names;
    for (const auto &item : db_->GetItems()) {
        item_names.push_back(QString::fromStdString(item.name()));
    }
    item_names.sort();
    item_list_->addItems(item_names);

    splitter_->addWidget(item_list_);
}

void MainWindow::_TestListRecipes() {
    recipes_from_item_->clear();

    QStringList recipe_label_list;
    for (const auto &recipe : db_->FindRecipes(item_list_->currentText().toStdString())) {
        recipe_label_list.push_back(QString::fromStdString(recipe.name()));
    }
    recipe_label_list.sort();
    recipes_from_item_->addItems(recipe_label_list);
}

/**
*
*/
void MainWindow::SDataSource() {
	auto data_source_dialog = new DataSourceDialog(this);
	if (data_source_dialog->exec() == QDialog::Accepted) {
        *db_ = gameData::Library(Settings::GetJsonDataPath().toStdString());
	}
}

/**
 *
 */
void MainWindow::SAbout() {
    auto *about_dialog = new AboutDialog(this);
    about_dialog->exec();
}

} // namespace ui