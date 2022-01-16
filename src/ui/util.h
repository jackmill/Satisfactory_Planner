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

/**
 * Generate QIcon from given item display name
 * @param display_name
 * @return
 */
inline QIcon itemIconFromDisplayName(const QString &display_name) {
    QString display_formatted = display_name;
	display_formatted.replace(' ', '_');
	auto icon_string = QString(":/icon/%1.png").arg(display_formatted);

    if (QFile(icon_string).exists()) {
        return QIcon(icon_string);
    } else {
        return QIcon(":/icon/No_Image_Available.png");
    }
}

/**
 * Format numbers greater than 10,000 to be "##.#k", rounded.\n
 * @param num
 * @return
 */
inline QString formatItemNumber(int num) {
    if (num > 9999) {
		// 12345 to 123; 12399 to 124
		num = static_cast<int>(std::round(static_cast<float>(num) / 100));

		// 12345 becomes "12.3k", 12399 becomes "12.4k", 12551 becomes "13.0k"
		return QString("%1.%2k").arg(QString::number(num / 10), QString::number(num % 10));

    } else {
        return QString::number(num);
    }

//    return item_count_formatted;
}

}

#endif //SATISFACTORY_PLANNER_UTIL_H
