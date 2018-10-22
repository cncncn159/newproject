#include "cmsgbusiness.h"

CMsgBusiness::CMsgBusiness(QObject *parent) : QObject(parent)
{

}
CMsgBusiness::~CMsgBusiness()
{

}

void CMsgBusiness::onCommingMsg(const QByteArray &msg)
{   //这里可以对收到的msg进行处理
    Q_UNUSED(msg)
    signalSomethingComing(QString("sss"));
}
