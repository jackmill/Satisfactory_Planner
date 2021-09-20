/**
 * @file DataSourceDialog.h
 * Created by jackm on 9/18/2021
 */

#ifndef SATISFACTORY_PLANNER_DATASOURCEDIALOG_H
#define SATISFACTORY_PLANNER_DATASOURCEDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLineEdit>

namespace ui {

class DataSourceDialog : public QDialog {
  public:
	explicit DataSourceDialog(QWidget* parent = nullptr);
	void accept() final;
	
  private:
	QVBoxLayout* layout_ = nullptr;
	QLineEdit* json_path_ = nullptr;
	QDialogButtonBox* actions_ = nullptr;
	
	[[nodiscard]] bool allowOk() const;
	
  private slots:
	void JsonPathChanged();
    void ChooseJsonPath();
};

} // namespace ui

#endif //SATISFACTORY_PLANNER_DATASOURCEDIALOG_H
