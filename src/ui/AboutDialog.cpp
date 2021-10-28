/**
 * @project Satisfactory_Planner
 * @file AboutDialog.cpp
 *
 * @author Jackson Miller
 * @date 2021-09-13
 * @copyright (c) 2021 Jackson Miller
 */

#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QLabel>
#include <QApplication>

#include "AboutDialog.h"
#include "projectconfig.h"

namespace ui {

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent) {
    setWindowTitle(tr("About"));

    auto* layout = new QVBoxLayout(this);

    // Name
    auto* name = new QLabel(qApp->applicationDisplayName(), this);
    QFont font = name->font();
    font.setPointSize(16);
    name->setFont(font);
    name->setAlignment(Qt::AlignHCenter);
    layout->addWidget(name);

    // Version
    auto* version = new QLabel(tr("Version ") + config::kProject_version, this);
    font = version->font();
    font.setPointSize(12);
    version->setFont(font);
    version->setAlignment(Qt::AlignHCenter);
    layout->addWidget(version);

    // Action Buttons
    auto* actions = new QDialogButtonBox(QDialogButtonBox::Close, this);
    connect(actions, &QDialogButtonBox::rejected, this, &AboutDialog::close);
    layout->addWidget(actions, Qt::AlignHCenter);

}

} // namespace ui