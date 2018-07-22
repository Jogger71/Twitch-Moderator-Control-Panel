#include "bot.h"

#include <QDebug>

const QString Bot::CHANNEL_ONE = "channelOne";
const QString Bot::CHANNEL_TWO = "channelTwo";
const QString Bot::CHANNEL_THREE = "channelThree";
const QString Bot::CHANNEL_FOUR = "channelFour";
const QString Bot::CHANNEL_FIVE = "channelFive";
const QString Bot::CHANNEL_SIX = "channelSix";

Bot::Bot(QObject *parent): IrcConnection(parent)
{
    parser.addCommand(IrcCommand::CtcpAction, "ACT [target] <message...>");
    parser.addCommand(IrcCommand::Custom, "HELP (<command...>)");
    parser.addCommand(IrcCommand::Nick, "NICK <nick>");
    parser.addCommand(IrcCommand::Join, "JOIN <#channel> (<key>)");
    parser.addCommand(IrcCommand::Part, "PART (<#channel>) (<message...>)");
    parser.addCommand(IrcCommand::Quit, "QUIT (<message...>)");
    parser.addCommand(IrcCommand::Message, "SAY [target] <message...>");

    QSettings settings;

    bufferModel.setConnection(this);

    connect(this, SIGNAL(privateMessageReceived(IrcPrivateMessage*)), this, SLOT(processMessage(IrcPrivateMessage*)));
}

void Bot::setupBot(User* user) {
    setHost(TWITCH_URL);
    setUserName(user->getUsername());
    setNickName(user->getUsername());
    setRealName(user->getUsername());
    setPassword(user->getOauthToken());
}

void Bot::processMessage(IrcPrivateMessage *message) {
    qDebug() << "Message: " << message->content();
    if (message->isPrivate()) {
        qDebug() << "Target (Nick):" <<  message->nick();
    } else {
        qDebug() << "Target:" << message->target();
    }
    sendCommand(IrcCommand::createMessage(message->target(), "Message Recieved!"));
}

void Bot::join(QString channel) {
    sendCommand(IrcCommand::createJoin(channel));
}

void Bot::part(QString channel) {
    sendCommand(IrcCommand::createPart(channel));
}

QStringList Bot::getChannelList() {
    return bufferModel.channels();
}

bool Bot::channelJoined(QString channel) {
    return (getChannelList().contains(channel));
}
