#ifndef CMSGBUSINESS_H
#define CMSGBUSINESS_H

#include <QObject>

#define FRAME_HEX_HEADER 	0x68
#define FRAME_HEX_TAIL		0x7f 
#define TIMER_TIMEOUT		1000u
#define HEART_WAIT_TIME		5u

typedef struct
{
	uint8_t len;
	uint8_t data[50];
}sFrameData;

typedef struct
{
	uint8_t 	header;	//帧头
	uint16_t	len;	//帧长度
	eFrameType 	type;	//帧类型
	uint8_t		version;//版本号
	uint16_t	hard;	//硬件
	sFrameData	FrameData;
	uint8_t		tail;	//帧尾
}sFrame;

typedef enum
{
	E_FRAME_HANDSHAKE = 1,				//握手
	E_FRAME_HEARTBEAT,					//心跳
	E_FRAME_DETECTION,					//检测
	E_FRAME_MEASURING,					//测量中
	E_FRAME_END_MEASURE,				//测量结束
	E_FRAME_DATA_MEASURE,				//测量数据
	E_FRAME_INQUIRE_MEASURE				//测量查询
}eFrameType;							//帧类型

typedef enum
{
	E_INIT_STAGE,						//初始化状态
	E_WORK_STAGE						//工作状态
}eWorkingStage;

//class Message;
class CMsgBusiness : public QObject
{
    Q_OBJECT
public:
    explicit CMsgBusiness(QObject *parent = 0);
    ~CMsgBusiness();
    //这里可以在UI里来直接调用
    QString get()const;
	virtual void timerEvent(QTimerEvent *event);

private:
	sFrame protocol_data;
	uint8_t dataDeal(QByteArray);
	uint8_t appDeal(sFrame frame);
	eWorkingStage work_stage;
	uint16_t timer_id;
	uint16_t heart_time;
signals:
    //处理完的Msg发到界面上去显示
    void signalSomethingComing(QByteArray);
	//下发命令到comm层
	void signalToSend(QByteArray);
private slots:
    //收到下层来的msg
    void onCommingMsg(const QByteArray);
	//收到界面上的动作
	void onCommingAct(const QByteArray);
public slots:
};



#endif // CMSGBUSINESS_H
