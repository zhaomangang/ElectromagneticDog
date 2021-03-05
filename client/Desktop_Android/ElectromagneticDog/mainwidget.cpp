#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "friendbutton.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget),
    login(NULL),
    socket(NULL)
{
    ui->setupUi(this);
    m_networkManager = new QNetworkAccessManager();
    this->hide();   //隐藏主界面
    if (NULL == socket)
    {
        socket = new ChatSocket;
    }
    if (NULL == login)
    {
        //创建登录对象
        qDebug()<<"login is null";
        login = new Login(socket);
    }
    if (NULL != login)
    {
        qDebug()<<"login not null";
        login->show();  //显示登录界面
    }
    music_mange = new Music(this);
    connect(login->getServerInfo(),SIGNAL(setInfoSuccess(QString,uint)),
           socket,SLOT(slotConnectToServer(QString,uint)));
    connect(socket,SIGNAL(logonSuccess(int,QString,QString)),this,SLOT(slotLogonSuccess(int,QString,QString)));
    connect(m_networkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(slotReplyFinished(QNetworkReply *)));

}

void MainWidget::slotLogonSuccess(int id, QString username, QString icon)
{
    this->show();
    if (NULL != login)
    {
        login->hide();
        delete login;
    }
    ui->label_username->setText(username);
    ui->label_3->setText(QString("id:%1").arg(id));

    layout_friend = new QVBoxLayout();
    layout_group = new QVBoxLayout();
    ui->toolBox->widget(0)->setLayout(layout_friend);
    ui->toolBox->widget(1)->setLayout(layout_group);

    QNetworkRequest request;
    request.setUrl(QUrl(icon));
    m_networkManager->get(request);
    /***demo****/
    FriendButton *fb = new FriendButton(1001,":/resource/login.png","mason");
    layout_friend->addWidget(fb->getButton());
}


// 响应结束，进行结果处理-图片显示或错误处理
void MainWidget::slotReplyFinished(QNetworkReply *reply)
{

    // 获取响应状态码，200表示正常
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();
        QPixmap pixmap;
        pixmap.loadFromData(bytes);
        QSize picSize(64,64);
        pixmap.scaled(picSize, Qt::KeepAspectRatio);
        ui->label_icon->setPixmap(pixmap);
    }
    else
    {
        // 错误处理-显示错误信息，或显示上一次缓存的图片或叉图。
    }
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_pushButton_3_clicked()
{
    music_mange->sortMusic(ui->sort_text->text());
}
