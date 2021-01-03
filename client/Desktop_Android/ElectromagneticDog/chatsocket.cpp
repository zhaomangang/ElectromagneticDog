#include "chatsocket.h"
#include "fixedvalue.h"
#include "apply_protocl.h"
ChatSocket::ChatSocket(QObject *parent) : QObject(parent),client_socket(NULL)
{
    if (NULL == client_socket)
    {
        client_socket = new QTcpSocket();
    }
    client_socket->connectToHost(QHostAddress(DEFAULT_IP),DEFAULT_PORT);
    qDebug()<<"connect "<<QHostAddress(DEFAULT_IP)<<DEFAULT_PORT;
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

void ChatSocket::sendLogin(unsigned int id, QString user, QString password)
{
    //1. 创建各个节点元素
  QJsonObject json;

  json={{NODE_TYPE, TYPE_LOGIN},{NODE_ID, int(id)}, {NODE_USERNAME, user},  {NODE_PASSWORD, password}};
  QJsonDocument doc(json);   //直接使用构造函数
  QByteArray ba = doc.toJson(QJsonDocument::Indented);

  client_socket->write(ba);
}
