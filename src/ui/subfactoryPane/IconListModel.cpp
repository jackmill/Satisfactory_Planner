/**
 * @project Satisfactory_Planner
 * @file IconListModel.cpp
 * 
 * @author Jackson Miller
 * @date 2021-12-31
 * @copyright (c) 2021 Jackson Miller
 */

#include <QDir>
#include <QIcon>

#include "IconListModel.h"

namespace ui {

IconListModel::IconListModel(QObject* parent) :
		QAbstractListModel(parent) {
	QFileInfoList icons = QDir(":/icon/").entryInfoList(QDir::Files);

	icon_strings_.push_back("None");
	for (const auto& icon : icons) {
		icon_strings_.push_back(icon.fileName());
	}
}

int IconListModel::rowCount(const QModelIndex& parent) const {
	return static_cast<int>(icon_strings_.size());
}

int IconListModel::columnCount(const QModelIndex& parent) const {
	return 1;
}

QVariant IconListModel::data(const QModelIndex& index, int role) const {
	const auto icon_string = icon_strings_.at(index.row());

	if (role == Qt::ItemDataRole::DecorationRole) {
		return QIcon(QString(":/icon/%1").arg(icon_string));
	} else if (role == Qt::ItemDataRole::DisplayRole) {
		QString displayed_string = icon_string;
		displayed_string.replace('_',' ');
		displayed_string.remove(R"(.png)");
		return displayed_string;
	}

	return {};
}

QString IconListModel::getIconString(int index) const {
	return icon_strings_.at(index);
}

int IconListModel::findIconIndex(const QString& icon_string) const {
	if (icon_strings_.contains(icon_string)) {
		return icon_strings_.indexOf(icon_string);
	} else {
		return 0;
	}
}

} // namespace ui