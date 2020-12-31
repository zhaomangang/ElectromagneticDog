#include "login.h"
#include "mainwidget.h"
#include <QApplication>
#include "chatwidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;
    w.show();
    MainWidget m;
    m.show();
    ChatWidget c;
    c.show();


    return a.exec();
}
