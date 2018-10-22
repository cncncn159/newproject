#include "cbridge.h"
#include "cport.h"
#include "cmsgbusiness.h"

CBridge::CBridge(QObject *parent) : QObject(parent)
{
    pBusiness = new CMsgBusiness(this);
    pPort = new CPort();
    //通讯层与业务层的通讯
    connect(pPort,SIGNAL(signalUpwardMsg(QByteArray)),pBusiness,SLOT(onCommingMsg(QByteArray)));
}

CBridge::~CBridge()
{

}

CBridge *CBridge::business() const
{
    return pBusiness;
}

CPort* CBridge::port() const
{
    return pPort;
}
