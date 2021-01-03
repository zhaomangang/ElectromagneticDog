#ifndef CHATSOCKET_H
#define CHATSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
class ChatSocket : public QObject
{
    Q_OBJECT
public:
    explicit ChatSocket(QObject *parent = nullptr);


private:
    QTcpSocket* client_socket;  //客户端套接字
signals:


private slots:


public slots:
    void slotConnectToServer(QString ip,unsigned int port);
};

#endif // CHATSOCKET_H
