/**
 * @file ItemButtonLabel.cpp
 * Created by jackm on 9/18/2021
 */

#include <QPainter>
#include <QPainterPath>

#include "ItemButtonLabel.h"

ItemButtonLabel::ItemButtonLabel(const QString &text, QWidget *parent) :
	QLabel(parent) {
	setText(text);
	setAlignment(Qt::AlignRight);
	setStyleSheet("font: bold; color: white; background-color: #E59344; border-radius: 3px; margin-right: 1px; margin-left: 1px");
}