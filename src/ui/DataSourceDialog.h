/**
 * @project Satisfactory_Planner
 * @file DataSourceDialog.h
 *
 * @author Jackson Miller
 * @date 2021-09-18
 * @copyright (c) 2021 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_DATASOURCEDIALOG_H
#define SATISFACTORY_PLANNER_DATASOURCEDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QCheckBox>

namespace ui {

class DataSourceDialog : public QDialog {
  public:
	explicit DataSourceDialog(QWidget* parent = nullptr);
	void accept() final;
	
  private:
	QVBoxLayout* layout_ = nullptr;
	QLineEdit* json_path_ = nullptr;
    QCheckBox* events_ = nullptr;
	QDialogButtonBox* actions_ = nullptr;
	
	[[nodiscard]] bool allowOk() const;
	
  private slots:
	void JsonPathChanged();
    void ChooseJsonPath();
};

} // namespace ui

#endif //SATISFACTORY_PLANNER_DATASOURCEDIALOG_H
