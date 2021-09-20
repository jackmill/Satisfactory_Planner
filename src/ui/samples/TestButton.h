/**
 * @file TestButton.h
 * Created by jackm on 9/17/2021
 */

#ifndef SATISFACTORY_PLANNER_TESTBUTTON_H
#define SATISFACTORY_PLANNER_TESTBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

namespace ui {

class TestButton : public QPushButton {
  Q_OBJECT
  public:
	explicit TestButton(QWidget *parent = nullptr);
	
  signals:
	void rightClicked();
	void ctrlClicked();
	void shiftClicked();
	
  private:
	int count_ = 0;
	
	void Increment() { ++count_; this->setText(QString::number(count_)); };
	void Decrement() { --count_; this->setText(QString::number(count_)); };
	void Embiggen();
	void Emsmallen();
	
  private slots:
	void mousePressEvent(QMouseEvent* e) override;
};

}

#endif //SATISFACTORY_PLANNER_TESTBUTTON_H
