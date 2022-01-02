/**
 * @project Satisfactory_Planner
 * @file MainWindow.cpp
 *
 * @author Jackson Miller
 * @date 2021-09-13
 * @copyright (c) 2021 Jackson Miller
 */

#include <QTextEdit>
#include <QMessageBox>
#include <QFileDialog>
#include <QMenuBar>
#include <QCloseEvent>

#include <nlohmann/json.hpp>
#include <memory>
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
	
	// Load database from given Docs.json file, either stored or chosen by user
	if (Settings::GetJsonDataPath().isEmpty()) {
		QMessageBox::information(this,
                                 tr("No Docs.json file found"),
                                 tr("Choose Docs.json file path in settings"));

        S_dataSource();

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
    actions_.act_file_new = new QAction(tr("&New"), this);
    actions_.act_file_new->setShortcut(QKeySequence::New);
    connect(actions_.act_file_new, &QAction::triggered, this, &MainWindow::S_fileNew);

    // Save
    actions_.act_file_save = new QAction(tr("&Save"), this);
    actions_.act_file_save->setShortcut(QKeySequence::Save);
    connect(actions_.act_file_save, &QAction::triggered, this, &MainWindow::S_fileSave);

    // Save As
    actions_.act_file_save_as = new QAction(tr("Save &As"), this);
    actions_.act_file_save_as->setShortcut(QKeySequence::SaveAs);
    connect(actions_.act_file_save_as, &QAction::triggered, this, &MainWindow::S_fileSaveAs);

    // Open
    actions_.act_file_open = new QAction(tr("&Open"), this);
    actions_.act_file_open->setShortcut(QKeySequence::Open);
    connect(actions_.act_file_open, &QAction::triggered, this, &MainWindow::S_fileOpen);

	// Data Source
	actions_.act_data_source = new QAction(tr("Select &Data Source..."), this);
	connect(actions_.act_data_source, &QAction::triggered, this, &MainWindow::S_dataSource);
	
    // Quit
    actions_.act_quit = new QAction(QIcon::fromTheme("application-exit"), tr("&Quit"), this);
    actions_.act_quit->setShortcut(QKeySequence::Quit);
    connect(actions_.act_quit, &QAction::triggered, this, &MainWindow::close);

    // About
    actions_.act_help = new QAction(tr("&About"), this);
    connect(actions_.act_help, &QAction::triggered, this, &MainWindow::S_about);

    //About Qt
    actions_.act_help_about_qt = new QAction(tr("About &Qt"), this);
    connect(actions_.act_help_about_qt, &QAction::triggered, this, &MainWindow::S_aboutQt);
}

void MainWindow::InitMenu() {
    // File
    QMenu* menu_file = menuBar()->addMenu(tr("&File"));
    menu_file->addAction(actions_.act_file_new);
    menu_file->addAction(actions_.act_file_save);
    menu_file->addAction(actions_.act_file_save_as);
    menu_file->addAction(actions_.act_file_open);
	actions_.menu_recent_files = menu_file->addMenu(tr("&Recent Files"));
	updateRecents();
    menu_file->addSeparator();
	menu_file->addAction(actions_.act_data_source);
	menu_file->addSeparator();
    menu_file->addAction(actions_.act_quit);

    QMenu* menu_help = menuBar()->addMenu(tr("&Help"));
    menu_help->addAction(actions_.act_help);
    menu_help->addAction(actions_.act_help_about_qt);
}

void MainWindow::InitUI() {
    subfactory_pane_ = new SubfactoryPane(factory_, db_, contents_);
    splitter_->addWidget(subfactory_pane_);

    production_pane_ = new ProductionPane(factory_->subfactories_.at(0), db_, this);
    splitter_->addWidget(production_pane_);

    splitter_->setCollapsible(0, true);

    connect(subfactory_pane_, &SubfactoryPane::S_selectedSubfactoryChanged,
            this, &MainWindow::S_selectedSubfactoryChanged);
    connect(subfactory_pane_, &SubfactoryPane::S_factoryChanged, this, &MainWindow::S_factoryChanged);
    connect(production_pane_, &ProductionPane::S_factoryChanged, this, &MainWindow::S_factoryChanged);

    if (!windowFilePath().isEmpty()) {
        setWindowTitle(QFileInfo(windowFilePath()).fileName() + "[*]");
    } else {
		setWindowTitle("untitled[*]");
	}
}

bool MainWindow::askAboutUnsavedData() {
    if (isWindowModified()) {
        const QMessageBox::StandardButton save_choice = QMessageBox::question(this,
                                                                              tr("Unsaved Data"),
                                                                              tr("There is unsaved data.  Would you like to save?"),
                                                                              QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (save_choice == QMessageBox::Save) {
            S_fileSave();
            if (isWindowModified()) {
                // User Cancelled the saving process
                return false;
            }
        } else if (save_choice == QMessageBox::Cancel) {
            return false;
        }
    }

    return true;
}

void MainWindow::SaveTo(const QString &path) {
    try {
        factory_->save(path.toStdString());
        setWindowFilePath(path);
        setWindowModified(false);
	    addToRecents(path);
    } catch (std::runtime_error &e) {
        QMessageBox::critical(this,
                              tr("Error saving file"),
                              tr("The file %1 cannot be saved.").arg(path));
    }
}

void MainWindow::OpenFrom(const QString &path) {
    try {
        factory_.reset(new plan::Factory(path.toStdString(), db_->getDBMap()));
        setWindowFilePath(path);
        setWindowModified(false);
	    addToRecents(path);

        subfactory_pane_->deleteLater();
        production_pane_->deleteLater();
        InitUI();
        production_pane_->resizeAll();

    } catch (const nlohmann::json::parse_error &e) {
        QMessageBox::critical(this,
                              tr("Error opening file"),
                              tr("The file %1 is not valid: %2").arg(path, e.what()));
    } catch (const std::runtime_error &e) {
        QMessageBox::critical(this,
                              tr("Error opening file"),
                              tr("The file %1 could not be read:\n%2").arg(path, e.what()));
    }
}

void MainWindow::addToRecents(const QString& path) {
    QStringList recent_files = Settings::GetRecentFiles();
    if (!recent_files.contains(path)) {
        recent_files.push_front(path);
        while (recent_files.size() > Settings::GetRecentFilesCount()) {
            recent_files.removeLast();
        }
    } else {
        std::sort(recent_files.begin(), recent_files.end(), [&path](const QString& a, const QString& b){
            return a == path && b != path;
        });
    }
    Settings::SetRecentFiles(recent_files);
    updateRecents();
}

void MainWindow::updateRecents() {
	actions_.menu_recent_files->clear();
	if (Settings::GetRecentFiles().empty()) {
		QAction* open_recent_file = actions_.menu_recent_files->addAction(tr("No recent files"));
		open_recent_file->setEnabled(false);
	} else {
		for (const auto& path : Settings::GetRecentFiles()) {
			QAction* open_recent_file = actions_.menu_recent_files->addAction(path);
			connect(open_recent_file, &QAction::triggered, [path, this]() {
				if (!askAboutUnsavedData()) {
					return;
				}
				OpenFrom(path);
			});
		}
	}
}

void MainWindow::closeEvent(QCloseEvent* event) {
    if (!askAboutUnsavedData()) {
        event->ignore();
    } else {
        event->accept();
    }
}

void MainWindow::S_fileNew() {
    if (!askAboutUnsavedData()) {
        return;
    }

    factory_.reset(new plan::Factory);
    setWindowFilePath({});

    subfactory_pane_->deleteLater();
    production_pane_->deleteLater();
    InitUI();
}

void MainWindow::S_fileSave() {
    if (windowFilePath().isEmpty()) {
        S_fileSaveAs();
    } else {
        SaveTo(windowFilePath());
    }
}

void MainWindow::S_fileSaveAs() {
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

void MainWindow::S_fileOpen() {
    if (!askAboutUnsavedData()) {
        return;
    }

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

void MainWindow::S_dataSource() {
	auto* data_source_dialog = new DataSourceDialog(this);
	if (data_source_dialog->exec() == QDialog::Accepted) {
        db_.reset(new data::Library(Settings::GetJsonDataPath().toStdString(), Settings::GetIncludeEvents()));
	}
    data_source_dialog->deleteLater();
}


void MainWindow::S_about() {
    auto *about_dialog = new AboutDialog(this);
    about_dialog->exec();
}

void MainWindow::S_aboutQt() {
    QMessageBox::aboutQt(this);
}

void MainWindow::S_selectedSubfactoryChanged() {
    production_pane_->deleteLater();
    production_pane_ = new ProductionPane(subfactory_pane_->selectedSubfactory(), db_, this);
    production_pane_->resizeAll();
    splitter_->addWidget(production_pane_);
}

void MainWindow::S_factoryChanged() {
    setWindowModified(true);
}

} // namespace ui