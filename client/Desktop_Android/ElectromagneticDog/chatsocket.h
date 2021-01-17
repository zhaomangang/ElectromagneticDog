#ifndef CHATSOCKET_H
#define CHATSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QFile>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
class ChatSocket : public QObject
{
    Q_OBJECT
public:
    explicit ChatSocket(QObject *parent = nullptr);
    void checkConnect();
    void sendLogin(unsigned int id,QString username,QString password);  //示例
private:
    QTcpSocket* client_socket;  //客户端套接字
signals:
    void logonSuccess(int id,QString username,QString icon);
    void logonFailed();
private slots:


public slots:
    void slotConnectToServer(QString ip,unsigned int port);
    void slotRecv();
};

#endif // CHATSOCKET_H
