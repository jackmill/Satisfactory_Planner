/**
 * @file ItemButton.cpp
 * Created by jackm on 9/18/2021
 */

#include <QFile>

#include "ItemButton.h"

namespace ui {

/**
 * Constructor
 * @param display_name
 * @param item_count
 * @param parent
 */
ItemButton::ItemButton(QString display_name, const int &item_count, std::shared_ptr<QJsonArray> &db, QWidget *parent) :
	item_count_(item_count),
	db_(db),
	BasicItemButton(std::move(display_name), parent) {
	
	// Button Size
	auto button_size_ = new QSize(45, 45);
	setFixedSize(*button_size_);
	
	// Layout
	layout_ = new QVBoxLayout(this);
	layout_->setMargin(button_size_->width() / 15);
	layout_->addSpacerItem(new QSpacerItem(button_size_->width(), button_size_->height()));
	
	// Icon
	setIcon(itemIconFromDisplayName(item_name_));
	setIconSize(*button_size_ * 0.8);
	
	// Count Label
	item_count_label_ = new ItemButtonLabel(formatItemNumber(item_count_), this);
	QFont count_font = QFont(item_count_label_->font());
	count_font.setPixelSize(button_size_->height() / 4);
	item_count_label_->setFont(count_font);
	
	layout_->addWidget(item_count_label_, Qt::AlignRight, Qt::AlignRight);
	
	// Tooltip
	setToolTip(item_name_ + ": " + QString::number(item_count_));
}

/**
 *
 * @param count
 */
void ItemButton::setItemCount(const int &count) {
	item_count_ = count;
	item_count_label_->setText(formatItemNumber(count));
	setToolTip(item_name_ + ": " + QString::number(count));
}

/**
 * Formats numbers over 9,999 into format "##.#k"
 * @param num
 * @return
 */
QString ItemButton::formatItemNumber(const int &num) {
	QString item_count_formatted;
	if (num > 9999) {
		item_count_formatted = QString::number(num / 1000) + '.';
		item_count_formatted.append(QString::number(std::round((float)(num % 1000) / 100)) + 'k');
	} else {
		item_count_formatted = QString::number(num);
	}
	return item_count_formatted;
}

} // namespace ui