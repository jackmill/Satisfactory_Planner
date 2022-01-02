/**
 * @project Satisfactory_Planner
 * @file IconListModel.h
 * 
 * @author Jackson Miller
 * @date 2021-12-31
 * @copyright (c) 2021 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_ICONLISTMODEL_H
#define SATISFACTORY_PLANNER_ICONLISTMODEL_H

#include <QAbstractListModel>

namespace ui {

class IconListModel final : public QAbstractListModel {
  public:
	explicit IconListModel(QObject* parent = nullptr);

	[[nodiscard]] int rowCount(const QModelIndex& parent) const final;
	[[nodiscard]] int columnCount(const QModelIndex& parent) const final;
	[[nodiscard]] QVariant data(const QModelIndex& index, int role) const final;

	[[nodiscard]] QString getIconString(int index) const;
	[[nodiscard]] int findIconIndex(const QString& icon_string) const;

  private:
	QStringList icon_strings_;
};

} // namespace ui

#endif //SATISFACTORY_PLANNER_ICONLISTMODEL_H
