#include "user.h"

//  Additional Qt Includes
#include <QSettings>

User::User()
{
    load();
}

const QString User::USERNAME_SETTING = "username";
const QString User::OAUTH_SETTING = "oauthToken";

void User::setUsername(QString username) {
    this->username = username;
}

QString User::getUsername() {
    return username;
}

void User::setOauthToken(QString oauthToken) {
    this->oauthToken = oauthToken;
}

QString User::getOauthToken() {
    return oauthToken;
}

void User::load() {
    QSettings settings;
    setUsername(settings.value(USERNAME_SETTING, "").toString());
    setOauthToken(settings.value(OAUTH_SETTING, "").toString());

    //  Hard code for testing purposes
    //setUsername("JoggerTheLurkLord");
    //setOauthToken("oauth:3ygyni6x8e00ezqa02ouowpvyzq2yy");

    //setUsername("Jogger71");
    //setOauthToken("oauth:h1h2pbqeqfav5vl0y8m9sq7omm3c61");
}

void User::save() {
    QSettings settings;
    settings.setValue(USERNAME_SETTING, getUsername());
    settings.setValue(OAUTH_SETTING, getOauthToken());
}

bool User::isSetup() {
    return (!getUsername().isEmpty() && !getOauthToken().isEmpty());
}
