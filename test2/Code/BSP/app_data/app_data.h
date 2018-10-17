#ifndef APP_DADA_H__
#define APP_DADA_H__
#include "sys.h"
#include "scan.h"

#define NULL    ((void *)0)

#define FRAME_HEX_HEADER 	0x68
#define FRAME_HEX_TAIL		0x7f

#define SOFTWARE_VERSION	0x00	//软件版本

//帧类型
#define HANDSHAKE_FRAMETYPE		0x01	//握手

#define HEARTBEAT_FRAMETYPE		0x02	//心跳

#define DETECTION_FRAMETYPE		0x03	//检测

#define MEASURING_FRAMETYPE		0x04	//测量中

#define END_FRAMETYPE			0x05	//测量结束

#define DATA_FRAMETYPE			0x06	//测量数据
#define INQUIRE_FRAMETYPE		0x06	//测量查询

#define FIXATION_LEN			0x07	//固定长度

typedef struct
{
	u8 len;
	u8 data[50];
}sFrameData;

typedef struct 
{
	u8 	header;	//帧头
	u16 len;	//帧长度
	u8 	type;	//帧类型
	u8	version;//版本号
	u16 hard;	//硬件
	sFrameData FrameData;
	u8	tail;	//帧尾
}sFrame;

void AppDataDeal(const u8 *data,u16 len);

#endif