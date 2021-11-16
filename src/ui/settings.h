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
	DGSETTINGS_SETTING(QString, JsonDataPath, "")
    DGSETTINGS_SETTING(bool, IncludeEvents, false)
    DGSETTINGS_SETTING(QString, LastFileDialogPath, "")
};

#endif //SATISFACTORY_PLANNER_SETTINGS_H
