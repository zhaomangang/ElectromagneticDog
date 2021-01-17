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
    connect(client_socket,SIGNAL(readyRead()),this,SLOT(slotRecv()));
    qDebug()<<"connect "<<QHostAddress(DEFAULT_IP)<<DEFAULT_PORT;
}
void ChatSocket::slotRecv()
{
    /**解析包类型**/
    QByteArray allData = client_socket->readAll();//取出消息内容
    qDebug()<<allData;
    //收到新数据
    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &json_error));
    if(json_error.error != QJsonParseError::NoError)
    {
        qDebug() << "json error!"<<json_error.errorString();
        return;
    }
    QJsonObject rootObj = jsonDoc.object();
    //因为是预先定义好的JSON数据格式，所以这里可以这样读取
    int type = -1;
    type = rootObj[NODE_TYPE].toInt();
    qDebug()<<type;
    switch (type) {
    case TYPE_LOGON_SUCCESS:    /*登录成功消息*/
        qDebug()<<rootObj[NODE_ID].toInt()<<rootObj[NODE_USERNAME].toString()<<rootObj[NODE_ICON].toString();
        emit logonSuccess(rootObj[NODE_ID].toInt(),rootObj[NODE_USERNAME].toString(),rootObj[NODE_ICON].toString());
        break;
    case TYPE_LOGON_ERROR:  /*登录失败消息*/
        emit logonFailed();
        break;
    default:
        break;
    }

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
