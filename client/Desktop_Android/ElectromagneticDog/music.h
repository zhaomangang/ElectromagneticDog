#ifndef MUSIC_H
#define MUSIC_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QVector>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QFile>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include <QMediaPlayer>
#define KUWO_SORT_URL "http://search.kuwo.cn/r.s?client=kt&all=%1&pn=0&rn=10&uid=513022881&ver=kwplayer_ar_9.0.7.0_138.apk&vipver=1&ft=music&cluster=0&strategy=2012&encoding=utf8&rformat=json&vermerge=1&mobi=1"
#define KUWO_URL_GET    "http://antiserver.kuwo.cn/anti.s?type=convert_url&rid=%1&format=mp3&response=url"


#define STR_SONGNAME "SONGNAME"
#define STR_MUSICRID "MUSICRID"
#define STR_FARTIST "FARTIST"

#define MODE_ORDER  1
#define MODE_RANDOM 2
#define MODE_SINGLE 3

typedef struct _SONG_ {
    QString songname;   //歌曲名
    QString fartist;    //歌手名
    QString musicrid;   //id
    QString playurl;    //播放url
}SONG;


class Music : public QObject
{
    Q_OBJECT
public:
    explicit Music(QObject *parent = nullptr);
    void sortMusic(QString text);   //搜索音乐，结果会保存至sort_result_list
    void playMusic(SONG song);  //播放音乐
private:
    QNetworkAccessManager* m_sort;  //搜索request
    QNetworkAccessManager* m_music_url; //播放url请求
    QVector<SONG> sort_result_list; //搜索结果
    void analyzeSortResult(QByteArray bytes);   //处理搜索结果，保存至sort_result_list
    QMediaPlayer *player;
    SONG song_now;  //当前播放
    int play_mode;  //播放模式
signals:

public slots:
     void slotSortFinished(QNetworkReply *);
     void slotGetUrlFinished(QNetworkReply *);
};

#endif // MUSIC_H
