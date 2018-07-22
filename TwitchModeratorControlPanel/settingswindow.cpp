#include "settingswindow.h"
#include "ui_settingswindow.h"

#include <QSettings>

#include "mainwindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    QSettings settings;
    ui->twitchUsername->setText(settings.value(User::USERNAME_SETTING, "").toString());
    ui->twitchOauthToken->setText(settings.value(User::OAUTH_SETTING, "").toString());
}

QString SettingsWindow::getUsername() {
    return ui->twitchUsername->text();
}

QString SettingsWindow::getOauthToken() {
    return ui->twitchOauthToken->text();
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}
