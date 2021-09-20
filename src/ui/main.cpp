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
