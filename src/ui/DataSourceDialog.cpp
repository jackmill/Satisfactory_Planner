/**
 * @project Satisfactory_Planner
 * @file DataSourceDialog.cpp
 *
 * @author Jackson Miller
 * @date 2021-09-18
 * @copyright (c) 2021 Jackson Miller
 */

#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDir>
#include <QFileDialog>

#include "DataSourceDialog.h"
#include "settings.h"

namespace ui {

DataSourceDialog::DataSourceDialog(QWidget *parent) :
		QDialog(parent) {
	setWindowTitle(tr("Select Data Source"));
	resize(600, 100);
	
	layout_ = new QVBoxLayout(this);
	auto filepath_layout = new QHBoxLayout();
	
	// Path field
	json_path_ = new QLineEdit(Settings::GetJsonDataPath(), this);
	connect(json_path_, &QLineEdit::textChanged, this, &DataSourceDialog::JsonPathChanged);
	filepath_layout->addWidget(json_path_);
	
	// Choose Button
	auto choose_file = new QPushButton(tr("Choose..."), this);
	connect(choose_file, &QPushButton::clicked, this, &DataSourceDialog::ChooseJsonPath);
	filepath_layout->addWidget(choose_file);

    // Events
    events_ = new QCheckBox(tr("Include Events (FICSMAS)"), this);
    events_->setChecked(Settings::GetIncludeEvents());
	
	// Button WindowActions
	actions_ = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
	actions_->button(QDialogButtonBox::Ok)->setEnabled(allowOk());
	connect(actions_, &QDialogButtonBox::accepted, this, &DataSourceDialog::accept);
	connect(actions_, &QDialogButtonBox::rejected, this, &DataSourceDialog::reject);
	
	layout_->addLayout(filepath_layout);
    layout_->addWidget(events_);
	layout_->addWidget(actions_);
}

void DataSourceDialog::accept() {
	if (json_path_->text().isEmpty()) {
		QMessageBox::critical(this,
							  tr("JSON data file required"),
							  tr("You can't just leave this blank.  How did you even manage to click OK?"));
		return;
	}
	
//	const QDir json_file_path(json_path_->text());
	if (!QFile::exists(json_path_->text())) {
		QMessageBox::critical(this,
							  tr("Non-existent directory"),
							  tr("%1 does not exist").arg(json_path_->text()));
		return;
	}
	
	Settings::SetJsonDataPath(json_path_->text());
    Settings::SetIncludeEvents(events_->isChecked());
	QDialog::accept();
}

bool DataSourceDialog::allowOk() const {
	return !json_path_->text().isEmpty();
}

void DataSourceDialog::JsonPathChanged() {
	actions_->button(QDialogButtonBox::Ok)->setEnabled(allowOk());
}

void DataSourceDialog::ChooseJsonPath() {
	auto file_dialog = new QFileDialog(this);
	file_dialog->setAcceptMode(QFileDialog::AcceptOpen);
	file_dialog->setFileMode(QFileDialog::ExistingFile);
	if (json_path_->text().isEmpty()) {
		file_dialog->setDirectory(QDir::rootPath());
	} else {
		file_dialog->setDirectory(json_path_->text());
	}
	if (file_dialog->exec() == QFileDialog::Accepted) {
		json_path_->setText(file_dialog->selectedFiles().first());
	}
}

} // namespace ui