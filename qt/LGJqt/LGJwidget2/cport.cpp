#include "cport.h"
#include <QDebug>

CPort::CPort(QObject *parent) : QObject(parent)
{
    port = new QSerialPort(this);
#ifdef __arm__
    port->setPortName("/dev/ttymxcl");
#else
    port->setPortName("COM2");
#endif
    port->setBaudRate(QSerialPort::Baud9600);
    port->setDataBits(QSerialPort::Data8);
    port->setParity(QSerialPort::EvenParity);
    port->setStopBits(QSerialPort::OneStop);

    connect(port,SIGNAL(readyRead()),this,SLOT(onReadData()));
    if(!port->open(QIODevice::ReadWrite))
    {
        qDebug()<<"Port Can't open";
    }

    timer = new QTimer(this);
    timer->setInterval(10000);
    connect(timer,SIGNAL(timeout()),SLOT(onParse()));
    timer->start();

    this->moveToThread(&worker);
    worker.start(QThread::HighPriority);
}

CPort::~CPort()
{

}

void CPort::onDownwardMsg(const QByteArray & msg)
{
    port->write(msg);
}

void CPort::onReadData()
{
    data.append(port->readAll());
}

void CPort::onParse()
{
    for(int i = 0;i<data.size();i++)
    {
        //...此处加解析
    }
    QByteArray arry;
    signalUpwardMsg(arry);
}
