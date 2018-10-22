#ifndef CPORT_H
#define CPORT_H

#include <QObject>
#include <QSerialPort>
#include <QThread>
#include <QTimer>
#include <QByteArray>

class CPort : public QObject
{
    Q_OBJECT
public:
    explicit CPort(QObject *parent = nullptr);
    ~CPort();
signals:
    //向上层传送消息
    void signalUpwardMsg(const QByteArray&);

public slots:
    //上层传过来的消息发送到串口
    void onDownwardMsg(const QByteArray&);
    //读串口数据
    void onReadData();
    //在这里定时的解析收到的数据
    void onParse();
private:
    QSerialPort* port;
    QThread worker;
    QTimer* timer;
    QByteArray data;
};

#endif // CPORT_H
