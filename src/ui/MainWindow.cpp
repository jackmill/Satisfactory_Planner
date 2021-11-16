/**
 * @project Satisfactory_Planner
 * @file MainWindow.cpp
 *
 * @author Jackson Miller
 * @date 2021-09-13
 * @copyright (c) 2021 Jackson Miller
 */

#include <QMenuBar>
#include <memory>
#include <string>
#include <QTextEdit>
#include <QMessageBox>
#include <QFileDialog>
#include <nlohmann/json.hpp>
#include <fstream>

#include "settings.h"
#include "MainWindow.h"
#include "DataSourceDialog.h"
#include "AboutDialog.h"
#include "projectconfig.h"

namespace ui {

MainWindow::MainWindow(QWidget *parent)
    : db_ (new data::Library),
    factory_(new plan::Factory),
    QMainWindow(parent) {
    setWindowTitle(tr(config::kProject_display_name));
	
	// Load database from given Docs.json file, either stored or chosen by user
	if (Settings::GetJsonDataPath().isEmpty()) {
		QMessageBox::information(this,
                                 tr("No Docs.json file found"),
                                 tr("Choose Docs.json file path in settings"));

        SDataSource();

	} else {
        *db_ = data::Library(Settings::GetJsonDataPath().toStdString(), Settings::GetIncludeEvents());
    }
	
	contents_ = new QWidget(this);
	setCentralWidget(contents_);
	
	layout_ = new QHBoxLayout(contents_);
	splitter_ = new QSplitter(contents_);
	layout_->addWidget(splitter_);

    InitActions();
    InitMenu();
    InitUI();
}

void MainWindow::InitActions() {
    // File
    // Save
    actions_.act_file_save = new QAction(tr("&Save"), this);
    actions_.act_file_save->setShortcut(QKeySequence::Save);
    connect(actions_.act_file_save, &QAction::triggered, this, &MainWindow::SFileSave);

    // Save As
    actions_.act_file_save_as = new QAction(tr("Save &As"), this);
    actions_.act_file_save_as->setShortcut(QKeySequence::SaveAs);
    connect(actions_.act_file_save_as, &QAction::triggered, this, &MainWindow::SFileSaveAs);

    // Open
    actions_.act_file_open = new QAction(tr("&Open"), this);
    actions_.act_file_open->setShortcut(QKeySequence::Open);
    connect(actions_.act_file_open, &QAction::triggered, this, &MainWindow::SFileOpen);

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

void MainWindow::InitMenu() {
    // File
    QMenu* menu_file = menuBar()->addMenu(tr("&File"));
    menu_file->addAction(actions_.act_file_save);
    menu_file->addAction(actions_.act_file_save_as);
    menu_file->addAction(actions_.act_file_open);
    menu_file->addSeparator();
	menu_file->addAction(actions_.act_data_source);
	menu_file->addSeparator();
    menu_file->addAction(actions_.act_quit);

    QMenu* menu_help = menuBar()->addMenu(tr("&Help"));
    menu_help->addAction(actions_.act_help);
}

void MainWindow::InitUI() {
    subfactory_pane_ = new SubfactoryPane(factory_, db_, contents_);
    connect(subfactory_pane_, &SubfactoryPane::SSubfactoryChanged, this, &MainWindow::SSubfactoryChanged);
    splitter_->addWidget(subfactory_pane_);

    production_pane_ = new ProductionPane(factory_->subfactories_.at(0), db_, this);
    splitter_->addWidget(production_pane_);

    splitter_->setCollapsible(0, true);
}

void MainWindow::SaveTo(const QString &path) {
    try {
        factory_->save(path.toStdString());
        setWindowFilePath(path);
        setWindowModified(false);
    } catch (std::runtime_error &e) {
        QMessageBox::critical(this,
                              tr("Error saving file"),
                              tr("The file %1 cannot be saved.").arg(path));
    }
}

void MainWindow::OpenFrom(const QString &path) {
    try {
        factory_ = std::make_shared<plan::Factory>();
        setWindowFilePath(path);
        std::ifstream file(path.toStdString());
        if (!file.is_open() || file.fail()) {
            throw std::runtime_error("Failed to open file");
        }
        nlohmann::json json;
        file >> json;
        if (!json.contains("subfactories")) {
            throw std::runtime_error("Not a valid factory file");
        }

        // Construct subfactories and add them to the file
        for (const auto &json_subfac : json.at("subfactories")) {
            // Label and Icon
            auto temp_subfac = plan::Subfactory(json_subfac.at("name"), json_subfac.at("icon"));

            // Targets
            for (const auto &json_target : json_subfac.at("targets")) {
                auto temp_item = data::Item(json_target.at("class_name"), db_->getDBMap());
                temp_item.setRate(json_target.at("rate"));
                temp_subfac.addTarget(temp_item);
            }

            // Product lines
            for (const auto &json_line : json_subfac.at("product_lines")) {
                auto line_target = data::Item(json_line.at("target").at("class_name"), db_->getDBMap());
                line_target.setRate(json_line.at("target").at("rate"));
                line_target.setAmount(json_line.at("target").at("amount"));
                temp_subfac.addProductLine(plan::ProductLine(line_target,
                                                             data::Recipe(json_line.at("recipe"),
                                                                            db_->getDBMap())));
            }

            // Update Ingredients and Byproducts Lists
            temp_subfac.updateIngredients();
            temp_subfac.updateByproducts();

            // Add to Factory
            factory_->subfactories_.emplace_back(temp_subfac);
        }

        delete subfactory_pane_;
        delete production_pane_;
        InitUI();

    } catch (const nlohmann::json::parse_error &e) {
        QMessageBox::critical(this,
                              tr("Error opening file"),
                              tr("The file %1 is not valid").arg(path));
    } catch (const std::runtime_error &e) {
        QMessageBox::critical(this,
                              tr("Error opening file"),
                              tr("The file %1 could not be read:\n%2").arg(path, e.what()));
    }
}

void MainWindow::SFileSave() {
    if (windowFilePath().isEmpty()) {
        SFileSaveAs();
    } else {
        SaveTo(windowFilePath());
    }
}

void MainWindow::SFileSaveAs() {
    auto* file_dialog = new QFileDialog(this);
    file_dialog->setAcceptMode(QFileDialog::AcceptSave);
    file_dialog->setFileMode(QFileDialog::AnyFile);
    file_dialog->setDefaultSuffix(kFileSuffix);
    file_dialog->setDirectory(Settings::GetLastFileDialogPath());
    if (!windowFilePath().isEmpty()) {
        file_dialog->selectFile(windowFilePath());
    }
    if (file_dialog->exec() == QFileDialog::Accepted) {
        const QStringList &selected_files = file_dialog->selectedFiles();
        const QString &path = selected_files.front();
        SaveTo(path);
        QDir dir(path);
        dir.cdUp();
        Settings::SetLastFileDialogPath(dir.absolutePath());
    }
    file_dialog->deleteLater();
}

void MainWindow::SFileOpen() {
    // TODO: Save File Check

    auto* file_dialog = new QFileDialog(this);
    file_dialog->setAcceptMode(QFileDialog::AcceptOpen);
    file_dialog->setFileMode(QFileDialog::ExistingFile);
    file_dialog->setDefaultSuffix(kFileSuffix);
    file_dialog->setDirectory(Settings::GetLastFileDialogPath());
    if (file_dialog->exec() == QFileDialog::Accepted) {
        const QStringList &selected_files = file_dialog->selectedFiles();
        const QString &path = selected_files.front();
        OpenFrom(path);
        QDir dir(path);
        dir.cdUp();
        Settings::SetLastFileDialogPath(dir.absolutePath());
    }
    file_dialog->deleteLater();
}

void MainWindow::SDataSource() {
	auto* data_source_dialog = new DataSourceDialog(this);
	if (data_source_dialog->exec() == QDialog::Accepted) {
        *db_ = data::Library(Settings::GetJsonDataPath().toStdString(), Settings::GetIncludeEvents());
	}
    data_source_dialog->deleteLater();
}


void MainWindow::SAbout() {
    auto *about_dialog = new AboutDialog(this);
    about_dialog->exec();
}

void MainWindow::SSubfactoryChanged() {
    delete production_pane_;
    production_pane_ = new ProductionPane(subfactory_pane_->selectedSubfactory(), db_, this);
    splitter_->addWidget(production_pane_);
}

} // namespace ui