#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPalette>
#include <QDebug>
#include <QPushButton>

#include "settingswindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setBotConnectionStatus(false);
    bot = new Bot();
    user = new User();
    user->save();
    bot->setupBot(user);

    //  Process the signals and slots
    connectSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectSlots() {
    //  Connect some signals
    connect(bot, SIGNAL(connecting()), this, SLOT(botConnecting()));
    connect(bot, SIGNAL(connected()), this, SLOT(botConnected()));
    connect(bot, SIGNAL(disconnected()), this, SLOT(botDisconnected()));
}

void MainWindow::toggleChannelButtons(bool connected) {
    QPushButton* channelOne = ui->connectChannelOne;
    QPushButton* channelTwo = ui->connectChannelTwo;
    QPushButton* channelThree = ui->connectChannelThree;
    QPushButton* channelFour = ui->connectChannelFour;
    QPushButton* channelFive = ui->connectChannelFive;
    QPushButton* channelSix = ui->connectChannelSix;

    ui->connectChannelOne->setEnabled(connected);
    ui->connectChannelTwo->setEnabled(connected);
    ui->connectChannelThree->setEnabled(connected);
    ui->connectChannelFour->setEnabled(connected);
    ui->connectChannelFive->setEnabled(connected);
    ui->connectChannelSix->setEnabled(connected);
}

void MainWindow::on_connectBotButton_clicked()
{
    ui->connectBotButton->setEnabled(false);
    if(bot->isActive()) {
        bot->close();
    } else {
        bot->open();
    }
}

void MainWindow::on_userSettingsButton_clicked()
{
    qDebug() << "Clicked User Settings Button";
    SettingsWindow userSettings;
    if (userSettings.exec() == QDialog::Accepted) {
        user->setUsername(userSettings.getUsername());
        user->setOauthToken(userSettings.getOauthToken());
        user->save();
    }
}

void MainWindow::on_connectChannelOne_clicked()
{
    QString channel = ui->channelOne->text();
    if (!bot->channelJoined(channel)) {
        bot->join(channel);
        ui->connectChannelOne->setText("Disconnect");
    } else {
        bot->part(channel);
        ui->connectChannelOne->setText("Connect");
    }
}

void MainWindow::botConnecting() {
    ui->connectBotButton->setText("Connecting");

    ui->botConnectionStatus->setText("Connecting");
    QString stylesheet = "QLabel { color: red; }";
    ui->botConnectionStatus->setStyleSheet(stylesheet);
}

void MainWindow::botConnected() {
    //  Reenable the button again
    ui->connectBotButton->setEnabled(true);

    ui->botConnectionStatus->setText("Connected");
    QString stylesheet = "QLabel { color: green; }";
    ui->botConnectionStatus->setStyleSheet(stylesheet);
    ui->connectBotButton->setText("Disconnect Bot");
}

void MainWindow::botDisconnected() {
    //  Reenable the button again
    ui->connectBotButton->setEnabled(true);

    ui->botConnectionStatus->setText("Not Connected");
    QString stylesheet = "QLabel { color: red; }";
    ui->botConnectionStatus->setStyleSheet(stylesheet);
    //  Now we need to
    ui->connectBotButton->setText("Connect Bot");
}
