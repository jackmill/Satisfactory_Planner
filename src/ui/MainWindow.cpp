//
// Created by Jackson Miller on 9/13/21.
//
#include <QMenuBar>
#include <fstream>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <QTextEdit>
#include <QTextStream>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

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
    : db_(new QJsonArray),
	QMainWindow(parent) {
    setWindowTitle(tr(config::kProject_display_name));
	
	// TODO: Implement db updating/changing/etc
	if (!Settings::GetJsonDataPath().isEmpty()) {
		*db_ = LoadDb(Settings::GetJsonDataPath());
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
	InitRecipes();
	
	test_item_ = new ItemButton("Plastic", 1638, db_, this);
	layout_->addWidget(test_item_);
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

/**
 * +++PROOF OF CONCEPT+++
 */
void MainWindow::InitRecipes() {
    recipe_list_ = new QComboBox(this);
    QStringList recipe_list;

    // Look through each Array object
	for (auto native_class = db_->cbegin(); native_class != db_->cend(); ++native_class) {
		QJsonObject native_class_object = native_class->toObject();
		
		// Check "NativeClass" Key
		if (native_class_object.value("NativeClass") == "Class'/Script/FactoryGame.FGRecipe'") {
			// Look through each "Classes" array
			QJsonArray class_array = native_class_object.value("Classes").toArray();
			for (auto item = class_array.cbegin(); item != class_array.cend(); ++item) {
				QString produced_in = item->toObject().value("mProducedIn").toString();
				if (produced_in.contains("Build_ConstructorMk1_C") ||
					produced_in.contains("Build_AssemblerMk1_C") ||
					produced_in.contains("Build_ManufacturerMk1_C") ||
					produced_in.contains("Build_Blender_C") ||
					produced_in.contains("Build_OilRefinery_C") ||
					produced_in.contains("Build_Packager_C") ||
					produced_in.contains("Build_SmelterMk1_C") ||
					produced_in.contains("Build_FoundryMk1_C") ||
					produced_in.contains("Build_HadronCollider_C")
				) {
					recipe_list.push_back(item->toObject().value("mDisplayName").toString());
				}
			}
		}
	}

	recipe_list.sort();
    recipe_list_->addItems(recipe_list);
	splitter_->addWidget(recipe_list_);
}

/**
 * Creates a QJsonDocument object from a given file
 * @param file File Path
 * @return QJsonDocument
 */
QJsonArray MainWindow::LoadDb(const QString &file) {
	// TODO: Deal with UTF-16LE encoding
	
	QFile json_file(file);
	QByteArray file_contents;
	QJsonDocument json_doc;

	try {
		json_file.open(QFile::ReadOnly);
		file_contents = json_file.readAll();
		json_file.close();
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	
	try {
		json_doc = QJsonDocument().fromJson(file_contents);
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	
	return json_doc.array();
}

/**
*
*/
void MainWindow::SDataSource() {
	auto data_source_dialog = new DataSourceDialog(this);
	if (data_source_dialog->exec() == QDialog::Accepted) {
		*db_ = LoadDb(Settings::GetJsonDataPath());
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