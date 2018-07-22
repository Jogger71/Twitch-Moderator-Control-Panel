#ifndef USER_H
#define USER_H

//  Qt includes
#include <QString>
#include <QVariant>

class User
{
public:
    User();
    void setUsername(QString username);
    QString getUsername();
    void setOauthToken(QString oauthToken);
    QString getOauthToken();
    void load();
    void save();
    bool isSetup();
    static const QString USERNAME_SETTING;
    static const QString OAUTH_SETTING;

private:
    QString username;
    QString oauthToken;
};

#endif // USER_H
