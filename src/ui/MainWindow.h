//
// Created by Jackson Miller on 9/13/21.
//

#ifndef SATISFACTORY_PLANNER_MAINWINDOW_H
#define SATISFACTORY_PLANNER_MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>
#include <QHBoxLayout>
#include <QSplitter>
#include <QJsonArray>

#include "subfactoryPane/SubfactoryPane.h"
#include "elements/ItemButton.h"

namespace ui {

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr);

  private:
    struct Actions {
        // File
		QAction* act_data_source = nullptr;
        QAction* act_quit = nullptr;

        // Help
        QAction* act_help = nullptr;
    };
	
	Actions actions_;
	SubfactoryPane* subfactory_pane_ = nullptr;
	
	QWidget* contents_ = nullptr;
	QHBoxLayout* layout_ = nullptr;
	QSplitter* splitter_ = nullptr;
 
    QComboBox* recipe_list_ = nullptr;
	ItemButton* test_item_ = nullptr;
	
	std::shared_ptr<QJsonArray> db_;
	QJsonArray LoadDb(const QString &file);
	
    void InitRecipes();
    void InitActions();
    void InitMenu();

  private Q_SLOTS:
    // Actions
	void SDataSource();
    void SAbout();
};

} // namespace ui

#endif //SATISFACTORY_PLANNER_MAINWINDOW_H