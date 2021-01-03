#include "chatsocket.h"

ChatSocket::ChatSocket(QObject *parent) : QObject(parent),client_socket(NULL)
{

}

void ChatSocket::slotConnectToServer(QString ip, unsigned int port)
{
    //收到setinfo对象的success，与服务端建立连接
    qDebug()<<ip<<" "<<port;
    if (NULL == client_socket)
    {
        client_socket = new QTcpSocket();
    }
    //主动和服务器建立连接
    client_socket->connectToHost(QHostAddress(ip),port);

}
