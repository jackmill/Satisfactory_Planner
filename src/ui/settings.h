/**
 * @file settings.h
 * Created by jackm on 9/18/2021
 */

#ifndef SATISFACTORY_PLANNER_SETTINGS_H
#define SATISFACTORY_PLANNER_SETTINGS_H

#include <dragoonboots/qsettingscontainer/QSettingsContainer.h>

class Settings : public dragoonboots::qsettingscontainer::QSettingsContainer {
  public:
	DGSETTINGS_SETTING(QString, JsonDataPath, "")
};

#endif //SATISFACTORY_PLANNER_SETTINGS_H
