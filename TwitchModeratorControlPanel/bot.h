#ifndef BOT_H
#define BOT_H

#include <QSettings>
#include <QString>
#include <QStringList>
#include <IrcConnection>
#include <IrcBufferModel>
#include <IrcCommandParser>
#include <IrcChannel>

#include "user.h"

class Bot: public IrcConnection
{
    Q_OBJECT
public:
    Bot(QObject *parent = 0);
    void setupBot(User* user);
    IrcCommand sendMessage(QString channel, QString message);
    void part(QString channel);
    QStringList getChannelList();
    bool channelJoined(QString channel);

    virtual ~Bot() {};

    static const QString CHANNEL_ONE;
    static const QString CHANNEL_TWO;
    static const QString CHANNEL_THREE;
    static const QString CHANNEL_FOUR;
    static const QString CHANNEL_FIVE;
    static const QString CHANNEL_SIX;

public slots:
    void join(QString channel);

private slots:
    void processMessage(IrcPrivateMessage* message);

private:
    IrcCommandParser parser;
    IrcBufferModel bufferModel;

    IrcChannel *channelOne;
    IrcChannel *channelTwo;
    IrcChannel *channelThree;
    IrcChannel *channelFour;
    IrcChannel *channelFive;
    IrcChannel *channelSix;

    QSettings settings;

    const QString TWITCH_URL = "irc.twitch.tv";
    const int TWITCH_IRC_PORT = 6667;
};

#endif // BOT_H
