#ifndef APP_DADA_H__
#define APP_DADA_H__
#include "sys.h"
#include "scan.h"

#define NULL    ((void *)0)

#define FRAME_HEX_HEADER 	0x68
#define FRAME_HEX_TAIL		0x7f

#define SOFTWARE_VERSION	0x00	//����汾

//֡����
#define HANDSHAKE_FRAMETYPE		0x01	

#define HEARTBEAT_FRAMETYPE		0x02

#define DETECTION_FRAMETYPE		0x03

#define MEASURING_FRAMETYPE		0x04

#define END_FRAMETYPE			0x05

#define DATA_FRAMETYPE			0x06
#define INQUIRE_FRAMETYPE		0x06

#define FIXATION_LEN			0x07

typedef struct
{
	u8 len;
	u8 data[50];
}sFrameData;

typedef struct 
{
	u8 	header;	//֡ͷ
	u16 len;	//֡����
	u8 	type;	//֡����
	u8	version;//�汾��
	u16 hard;	//Ӳ��
	sFrameData FrameData;
	u8	tail;	//֡β
}sFrame;

void AppDataDeal(const u8 *data,u16 len);

#endif