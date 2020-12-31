#ifndef CHATSOCKET_H
#define CHATSOCKET_H

#include <QObject>

class ChatSocket : public QObject
{
    Q_OBJECT
public:
    explicit ChatSocket(QObject *parent = nullptr);

signals:

public slots:
};

#endif // CHATSOCKET_H