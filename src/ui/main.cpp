/**
 * @project Satisfactory_Planner
 * @file main.cpp
 *
 * @author Jackson Miller
 * @date 2021-09-13
 * @copyright (c) 2021 Jackson Miller
 */

#include "projectconfig.h"

#include <QApplication>

#include "MainWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName(config::kProject_name);
    app.setApplicationDisplayName(config::kProject_display_name);
	app.setOrganizationName(config::kProject_organization_name);
	app.setOrganizationDomain(config::kProject_organization_domain);
    app.setApplicationVersion(config::kProject_version);

    ui::MainWindow main_window;
    main_window.show();

    return app.exec();
}
