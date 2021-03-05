#include "music.h"

Music::Music(QObject *parent) : QObject(parent)
{
    m_sort = new QNetworkAccessManager;
    m_music_url = new QNetworkAccessManager;
    player = new QMediaPlayer;
    connect(m_sort, SIGNAL(finished(QNetworkReply *)), this, SLOT(slotSortFinished(QNetworkReply *)));
    connect(m_music_url, SIGNAL(finished(QNetworkReply *)), this, SLOT(slotGetUrlFinished(QNetworkReply *)));

}

void Music::sortMusic(QString text)
{
    //搜索音乐
    QNetworkRequest request;
    text = QString(KUWO_SORT_URL).arg(text);
    qDebug()<<"sort music url:"<<text;
    request.setUrl(QUrl(text));
    m_sort->get(request);
    sort_result_list.clear();   //清空上一次搜索结果
}

void Music::analyzeSortResult(QByteArray bytes)
{
    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(bytes, &json_error));
    if(json_error.error != QJsonParseError::NoError)
    {
        qDebug() << "json error!"<<json_error.errorString();
        return;
    }
    QJsonObject rootObj = jsonDoc.object();
    QJsonArray absArr = rootObj["abslist"].toArray();
    for (int i = 0; i < absArr.size(); i++)
    {
        //将结果存入sort_result
        QJsonObject temp = absArr.at(i).toObject();
        qDebug()<<"songinfo:";
        qDebug()<<temp[STR_SONGNAME].toString();
        qDebug()<<temp[STR_MUSICRID].toString();
        SONG temp_song;
        temp_song.songname = temp[STR_SONGNAME].toString();
        temp_song.fartist = temp[STR_FARTIST].toString();
        temp_song.musicrid = temp[STR_MUSICRID].toString();
        sort_result_list.append(temp_song);
    }
    //测试程序，先试着播放搜索结果第一个
    playMusic(sort_result_list.first());

}

void Music::slotGetUrlFinished(QNetworkReply *reply)
{
    qDebug()<<"get end";
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();
        qDebug()<<"play url:"<<bytes;
        player->setMedia(QUrl(bytes));
        player->setVolume(10);
        qDebug()<<player->currentMedia().canonicalUrl().toString();
        player->play();
    }
    else
    {
        qDebug()<<"error";
        qDebug()<<reply->errorString();
    }
}

void Music::playMusic(SONG song)
{
    song_now = song;    //更新当前正在播放歌曲
    QNetworkRequest request;
    QString text = QString(KUWO_URL_GET).arg(song.musicrid);
    qDebug()<<"get play url:"<<text;
    request.setUrl(QUrl(text));
    m_music_url->get(request);
}


void Music::slotSortFinished(QNetworkReply *reply)
{
    //搜所结果
    // 获取响应状态码，200表示正常
    qDebug()<<"end";
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();
        analyzeSortResult(bytes);
    }
    else
    {
        qDebug()<<"error";
        qDebug()<<reply->errorString();
        // 错误处理-显示错误信息，或显示上一次缓存的图片或叉图。
    }
}
