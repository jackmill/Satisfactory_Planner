/**
 * @project Satisfactory_Planner
 * @file TableIcon.h
 * 
 * @author Jackson Miller
 * @date 2022-01-10
 * @copyright (c) 2022 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_TABLEICON_H
#define SATISFACTORY_PLANNER_TABLEICON_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

namespace ui {

class TableIcon : public QPushButton {
  public:
	TableIcon(const QString& icon_label, int rate, QWidget* parent);
	TableIcon(const QString& icon_label, float rate, QWidget* parent);
	TableIcon(const QString& icon_label, QWidget* parent);

	constexpr static const QSize kSize_ = QSize(50, 50);

  protected:
	QVBoxLayout* layout_ = nullptr;
	static void formatIconLabel(QLabel* label);

};

} // namespace ui

#endif //SATISFACTORY_PLANNER_TABLEICON_H
