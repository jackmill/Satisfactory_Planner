/**
 * @project Satisfactory_Planner
 * @file util.h
 *
 * @author Jackson Miller
 * @date 2021-10-05
 * @copyright (c) 2021 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_UTIL_H
#define SATISFACTORY_PLANNER_UTIL_H

#include <QFile>
#include <QIcon>

#include <cmath>

namespace ui::util {

inline QIcon itemIconFromDisplayName(const QString &display_name) {
    QString icon_string = display_name;
    icon_string.replace(' ', '_');
    icon_string.prepend(":/icon/");
    icon_string.append(".png");

    if (QFile(icon_string).exists()) {
        return QIcon(icon_string);
    } else {
        return QIcon(":/icon/No_Image_Available.png");
    }
}

inline QString formatItemNumber(const int &num) {
    QString item_count_formatted;
    if (num > 9999) {
        item_count_formatted = QString::number(num / 1000) + '.';
        item_count_formatted.append(QString::number(std::round(static_cast<float>(num % 1000) / 100)) + 'k');
    } else {
        item_count_formatted = QString::number(num);
    }
    return item_count_formatted;
}

}

#endif //SATISFACTORY_PLANNER_UTIL_H
