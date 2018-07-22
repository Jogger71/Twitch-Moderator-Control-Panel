#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStyle>

#include "user.h"
#include "bot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    User* user;
    Bot* bot;
    void connectSlots();
    void toggleChannelButtons(bool connected);
    void setBotConnectionStatus(bool connected);

private slots:
    void on_connectBotButton_clicked();

    void on_userSettingsButton_clicked();

    void on_connectChannelOne_clicked();

    void botConnecting();
    void botConnected();
    void botDisconnected();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
