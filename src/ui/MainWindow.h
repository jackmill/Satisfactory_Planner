/**
 * @project Satisfactory_Planner
 * @file MainWindow.h
 *
 * @author Jackson Miller
 * @date 2021-09-13
 * @copyright (c) 2021 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_MAINWINDOW_H
#define SATISFACTORY_PLANNER_MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>
#include <QHBoxLayout>
#include <QSplitter>

#include "data/Library.h"
#include "plan/Factory.h"

#include "subfactoryPane/SubfactoryPane.h"
#include "mainTable/ProductionPane.h"

namespace ui {

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = nullptr);

  private:
    struct WindowActions {
        // File
        QAction* act_file_new = nullptr;
        QAction* act_file_save = nullptr;
        QAction* act_file_save_as = nullptr;
        QAction* act_file_open = nullptr;
        QMenu*   menu_recent_files = nullptr;
		QAction* act_data_source = nullptr;
        QAction* act_quit = nullptr;

        // Help
        QAction* act_help = nullptr;
        QAction* act_help_about_qt = nullptr;
    };

    static inline const auto kFileSuffix = "json";

	WindowActions actions_;

	SubfactoryPane* subfactory_pane_ = nullptr;
    ProductionPane* production_pane_ = nullptr;
	
	QWidget* contents_ = nullptr;
	QHBoxLayout* layout_ = nullptr;
	QSplitter* splitter_ = nullptr;

    std::shared_ptr<data::Library> db_;
    std::shared_ptr<plan::Factory> factory_;

    void InitActions();
    void InitMenu();
    void InitUI();

    bool askAboutUnsavedData();
    void SaveTo(const QString &path);
    void OpenFrom(const QString &path);
    void addToRecents(const QString& path);
    void updateRecents();

    void closeEvent(QCloseEvent* event) override;

  private Q_SLOTS:
    // WindowActions
    void S_fileNew();
    void S_fileSave();
    void S_fileSaveAs();
    void S_fileOpen();
	void S_dataSource();
    void S_about();
    void S_aboutQt();

    //
    void S_selectedSubfactoryChanged();
    void S_factoryChanged();
};

} // namespace ui

#endif //SATISFACTORY_PLANNER_MAINWINDOW_H
