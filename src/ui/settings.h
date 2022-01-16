/**
 * @project Satisfactory_Planner
 * @file settings.h
 *
 * @author Jackson Miller
 * @date 2021-09-18
 * @copyright (c) 2021 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_SETTINGS_H
#define SATISFACTORY_PLANNER_SETTINGS_H

#include <dragoonboots/qsettingscontainer/QSettingsContainer.h>

class Settings : public dragoonboots::qsettingscontainer::QSettingsContainer {
  public:
	/** Window Geometry */
	DGSETTINGS_SETTING(QByteArray, MainWindowGeometry, {})

    /** Path to docs.json data source */
	DGSETTINGS_SETTING(QString, JsonDataPath, "")

    /** Include items and recipes from events like FICSMAS */
    DGSETTINGS_SETTING(bool, IncludeEvents, false)

    /** Last path opened in a file dialog */
    DGSETTINGS_SETTING(QString, LastFileDialogPath, "")

    /** Recently opened files */
    DGSETTINGS_SETTING(QStringList, RecentFiles, {})

    /** Number of recent files */
    DGSETTINGS_SETTING(int, RecentFilesCount, 4)
};

#endif //SATISFACTORY_PLANNER_SETTINGS_H
