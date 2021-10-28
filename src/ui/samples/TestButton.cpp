/**
 * @project Satisfactory_Planner
 * @file TestButton.cpp
 *
 * @author Jackson Miller
 * @date 2021-09-17
 * @copyright (c) 2021 Jackson Miller
 */

#include "TestButton.h"

namespace ui {

TestButton::TestButton(QWidget *parent) :
		QPushButton(parent) {
	setText(QString::number(count_));
	
	connect(this, &TestButton::clicked, this, &TestButton::Increment);
	connect(this, &TestButton::rightClicked, this, &TestButton::Decrement);
	connect(this, &TestButton::ctrlClicked, this, &TestButton::Embiggen);
	connect(this, &TestButton::shiftClicked, this, &TestButton::Emsmallen);
}

void TestButton::mousePressEvent(QMouseEvent *e) {
	if (e->button() == Qt::RightButton && e->modifiers() == Qt::NoModifier) {
		emit rightClicked();
	} else if (e->button() == Qt::LeftButton && e->modifiers() == Qt::NoModifier) {
		emit clicked();
	}
	
	if (e->modifiers() == Qt::ControlModifier) {
		emit ctrlClicked();
	} else if (e->modifiers() == Qt::ShiftModifier) {
		emit shiftClicked();
	}
}

void TestButton::Embiggen() {
	QFont btn_font = font();
	btn_font.setPointSize(btn_font.pointSize() + 1);
	setFont(btn_font);
	setText(QString::number(count_));
}

void TestButton::Emsmallen() {
	QFont btn_font = font();
	btn_font.setPointSize(btn_font.pointSize() - 1);
	setFont(btn_font);
	setText(QString::number(count_));
}

}