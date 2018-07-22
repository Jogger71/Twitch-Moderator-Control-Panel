#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //  Set up the settings information
    QCoreApplication::setOrganizationName("Adrian Du Plessi");
    QCoreApplication::setOrganizationDomain("sugarcoding.co.za");
    QCoreApplication::setApplicationName("Twitch Moderator Control Panel");

    w.show();

    return a.exec();
}
